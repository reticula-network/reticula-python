#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <fmt/format.h>
#include <dag/components.hpp>

#include "type_str/components.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_component_types {
  void operator()(py::module &m) {
    using Component = dag::component<VertT>;
    py::class_<Component>(m,
        python_type_str<Component>().c_str())
      .def(py::init<std::size_t>(),
          "size_hint"_a = 0)
      .def(py::init<std::vector<VertT>, std::size_t>(),
          "vertices"_a, "size_hint"_a = 0)
      .def("insert",
          static_cast<void (Component::*)(
            const VertT&)>(
            &Component::insert),
          "vertex"_a)
      .def("insert",
          static_cast<void (Component::*)(
            const std::vector<VertT>&)>(
            &Component::insert),
          "vertex"_a)
      .def("merge", &Component::merge,
          "other"_a)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def("__iter__", [](const Component& c) {
            return py::make_iterator(c.begin(), c.end());
          }, py::keep_alive<0, 1>())
      .def("__len__", &Component::size)
      .def("__contains__", &Component::contains,
          "vertex"_a)
      .def("__repr__", [](const Component& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename Component::VertexType>();
      });

    using ComponentSize = dag::component_size<VertT>;
    py::class_<ComponentSize>(m,
        python_type_str<ComponentSize>().c_str())
      .def("size", &ComponentSize::size)
      .def("__repr__", [](const ComponentSize& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename ComponentSize::VertexType>();
      });

    using ComponentSizeEstimate =
      dag::component_size_estimate<VertT>;
    py::class_<ComponentSizeEstimate>(m,
        python_type_str<ComponentSizeEstimate>().c_str())
      .def("size_estimate",
          &ComponentSizeEstimate::size_estimate)
      .def("__repr__", [](const ComponentSizeEstimate& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename ComponentSizeEstimate::VertexType>();
      });
  }
};

void declare_typed_components(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_component_types>,
      types::all_vert_types>>{}(m);
}
