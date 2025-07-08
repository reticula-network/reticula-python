#include "bind_core.hpp"
#include <nanobind/operators.h>
#include <nanobind/make_iterator.h>

#include <fmt/format.h>

#include <reticula/intervals.hpp>

#include "type_str/intervals.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <typename TimeT>
struct declare_interval_set_types {
  void operator()(nb::module_& m) {
    using IntSet = reticula::interval_set<TimeT>;
    nb::class_<IntSet>(
        m, python_type_str<IntSet>().c_str())
      .def(nb::init<>(),
          nb::call_guard<nb::gil_scoped_release>())
      .def("insert",
          &IntSet::insert,
          "start"_a, "end"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("merge",
          &IntSet::merge,
          "other"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("covers",
          &IntSet::covers,
          "time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("cover",
          &IntSet::cover,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__iter__", [](const IntSet& c) {
            return nb::make_iterator(
                    nb::type<IntSet>(), "iterator",
                    c.begin(), c.end());
          }, nb::keep_alive<0, 1>())
      .def("__contains__",
          &IntSet::covers,
          "time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::self == nb::self,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__copy__", [](const IntSet& self) {
          return IntSet(self);
      }).def("__deepcopy__", [](const IntSet& self, nb::dict) {
          return IntSet(self);
      }, "memo"_a)
      .def("__repr__", [](const IntSet& c) {
          return fmt::format("{}", c);
      }).def_static("value_type", []() {
        return types::handle_for<typename IntSet::ValueType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<IntSet>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<IntSet>{}();
      });
  }
};
}

void declare_typed_interval_sets(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_interval_set_types>,
      types::time_types>>{}(m);
}
