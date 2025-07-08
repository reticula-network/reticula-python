#include <vector>
#include <unordered_set>

#include "bind_core.hpp"
#include <nanobind/operators.h>
#include <nanobind/make_iterator.h>

#include <fmt/format.h>
#include <reticula/components.hpp>

#include "type_str/components.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT>
struct declare_component_types {
  void operator()(nb::module_& m) {
    using Component = reticula::component<VertT>;
    nb::class_<Component>(m,
        python_type_str<Component>().c_str())
      .def("__init__", [](Component* c, std::size_t size_hint){
           new (c) Component(size_hint);
       }, "size_hint"_a = 0,
           nb::call_guard<nb::gil_scoped_release>())
      .def(nb::init<Component>(),
          "component"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::init<std::vector<VertT>, std::size_t>(),
          "vertices"_a, "size_hint"_a = 0,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::init<std::unordered_set<
            VertT, reticula::hash<VertT>>, std::size_t>(),
          "vertices"_a, "size_hint"_a = 0,
          nb::call_guard<nb::gil_scoped_release>())
      .def("insert",
          static_cast<void (Component::*)(
            const VertT&)>(
            &Component::insert),
          "vertex"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("insert",
          static_cast<void (Component::*)(
            const std::vector<VertT>&)>(
            &Component::insert),
          "vertex"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("merge", &Component::merge,
          "other"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::self == nb::self,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::self != nb::self,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__iter__", [](const Component& c) {
            return nb::make_iterator(
                    nb::type<Component>(), "iterator",
                    c.begin(), c.end());
          }, nb::keep_alive<0, 1>())
      .def("__len__", &Component::size,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__contains__", &Component::contains,
          "vertex"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__copy__", [](const Component& self) {
          return Component(self);
      }).def("__deepcopy__", [](const Component& self, nb::dict) {
          return Component(self);
      }, "memo"_a)
      .def("__repr__", [](const Component& c) {
          return fmt::format("{}", c);
      }).def_static("vertex_type", []() {
        return types::handle_for<typename Component::VertexType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<Component>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<Component>{}();
      });

    nb::implicitly_convertible<
      std::unordered_set<VertT, reticula::hash<VertT>>,
      reticula::component<VertT>>();

    using ComponentSize = reticula::component_size<VertT>;
    nb::class_<ComponentSize>(m,
        python_type_str<ComponentSize>().c_str())
      .def("size", &ComponentSize::size,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__copy__", [](const ComponentSize& self) {
          return ComponentSize(self);
      }).def("__deepcopy__", [](const ComponentSize& self, nb::dict) {
          return ComponentSize(self);
      }, "memo"_a)
      .def("__repr__", [](const ComponentSize& c) {
          return fmt::format("{}", c);
      }).def_static("vertex_type", []() {
        return types::handle_for<typename ComponentSize::VertexType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<ComponentSize>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<ComponentSize>{}();
      });

    using ComponentSizeEstimate =
      reticula::component_size_estimate<VertT>;
    nb::class_<ComponentSizeEstimate>(m,
        python_type_str<ComponentSizeEstimate>().c_str())
      .def("size_estimate",
          &ComponentSizeEstimate::size_estimate,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__copy__", [](const ComponentSizeEstimate& self) {
          return ComponentSizeEstimate(self);
      }).def("__deepcopy__", [](const ComponentSizeEstimate& self, nb::dict) {
          return ComponentSizeEstimate(self);
      }, "memo"_a)
      .def("__repr__", [](const ComponentSizeEstimate& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename ComponentSizeEstimate::VertexType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<ComponentSizeEstimate>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<ComponentSizeEstimate>{}();
      });
  }
};
}

void declare_typed_components(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_component_types>,
      types::all_vert_types>>{}(m);
}
