#include <vector>
#include <unordered_set>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <fmt/format.h>
#include <reticula/components.hpp>

#include "metaclass.hpp"
#include "type_str/components.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"
#include "metaclass.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_component_types {
  void operator()(py::module &m, PyObject* metaclass) {
    using Component = reticula::component<VertT>;
    py::class_<Component>(m,
        python_type_str<Component>().c_str(),
        py::metaclass(metaclass))
      .def(py::init<std::size_t>(),
          "size_hint"_a = 0,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init<Component>(),
          "component"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init<std::vector<VertT>, std::size_t>(),
          "vertices"_a, "size_hint"_a = 0,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init<std::unordered_set<
            VertT, reticula::hash<VertT>>, std::size_t>(),
          "vertices"_a, "size_hint"_a = 0,
          py::call_guard<py::gil_scoped_release>())
      .def("insert",
          static_cast<void (Component::*)(
            const VertT&)>(
            &Component::insert),
          "vertex"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("insert",
          static_cast<void (Component::*)(
            const std::vector<VertT>&)>(
            &Component::insert),
          "vertex"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("merge", &Component::merge,
          "other"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::self == py::self,
          py::call_guard<py::gil_scoped_release>())
      .def(py::self != py::self,
          py::call_guard<py::gil_scoped_release>())
      .def("__iter__", [](const Component& c) {
            return py::make_iterator(c.begin(), c.end());
          }, py::keep_alive<0, 1>())
      .def("__len__", &Component::size,
          py::call_guard<py::gil_scoped_release>())
      .def("__contains__", &Component::contains,
          "vertex"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("__repr__", [](const Component& c) {
          return fmt::format("{}", c);
      }).def_static("vertex_type", []() {
        return types::handle_for<typename Component::VertexType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<Component>{}());
      });

    py::implicitly_convertible<
      std::unordered_set<VertT, reticula::hash<VertT>>,
      reticula::component<VertT>>();

    using ComponentSize = reticula::component_size<VertT>;
    py::class_<ComponentSize>(m,
        python_type_str<ComponentSize>().c_str(),
        py::metaclass(metaclass))
      .def("size", &ComponentSize::size,
          py::call_guard<py::gil_scoped_release>())
      .def("__repr__", [](const ComponentSize& c) {
          return fmt::format("{}", c);
      }).def_static("vertex_type", []() {
        return types::handle_for<typename ComponentSize::VertexType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<ComponentSize>{}());
      });

    using ComponentSizeEstimate =
      reticula::component_size_estimate<VertT>;
    py::class_<ComponentSizeEstimate>(m,
        python_type_str<ComponentSizeEstimate>().c_str(),
        py::metaclass(metaclass))
      .def("size_estimate",
          &ComponentSizeEstimate::size_estimate,
          py::call_guard<py::gil_scoped_release>())
      .def("__repr__", [](const ComponentSizeEstimate& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename ComponentSizeEstimate::VertexType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<ComponentSizeEstimate>{}());
      });
  }
};

void declare_typed_components(py::module& m) {
  auto metaclass = common_metaclass("_reticula_ext.component_metaclass");

  types::run_each<
    metal::transform<
      metal::lambda<declare_component_types>,
      types::all_vert_types>>{}(m, (PyObject*)metaclass);
}
