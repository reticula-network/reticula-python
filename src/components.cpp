#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>

#include <fmt/format.h>
#include <dag/components.hpp>

#include "type_str/components.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT>
struct declare_component_types {
  void operator()(nb::module_ &m) {
    using Component = dag::component<VertT>;
    nb::class_<Component>(m,
        python_type_str<Component>().c_str())
      .def(nb::init<std::size_t>(),
          "size_hint"_a = 0)
      .def(nb::init<std::vector<VertT>, std::size_t>(),
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
      .def(nb::self == nb::self)
      .def(nb::self != nb::self)
      .def("__iter__", [](const Component& c) {
            return nb::make_iterator(c.begin(), c.end());
          }, nb::keep_alive<0, 1>())
      .def("__len__", &Component::size)
      .def("__contains__", &Component::contains,
          "vertex"_a)
      .def("__repr__", [](const Component& c) {
          return fmt::format("{}", c);
      });

    using ComponentSize = dag::component_size<VertT>;
    nb::class_<ComponentSize>(m,
        python_type_str<ComponentSize>().c_str())
      .def("size", &ComponentSize::size)
      .def("__repr__", [](const ComponentSize& c) {
          return fmt::format("{}", c);
      });

    using ComponentSizeEstimate =
      dag::component_size_estimate<VertT>;
    nb::class_<ComponentSizeEstimate>(m,
        python_type_str<ComponentSizeEstimate>().c_str())
      .def("size_estimate",
          &ComponentSizeEstimate::size_estimate)
      .def("__repr__", [](const ComponentSizeEstimate& c) {
          return fmt::format("{}", c);
      });
  }
};

void declare_typed_components(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_component_types>,
      types::all_vert_types>>{}(m);
}
