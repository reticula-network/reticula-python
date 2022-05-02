#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl.h>
#include <fmt/format.h>

#include <dag/intervals.hpp>

#include "type_str/intervals.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename TimeT>
struct declare_interval_set_types {
  void operator()(nb::module &m) {
    using IntSet = dag::interval_set<TimeT>;
    nb::class_<IntSet>(m,
        python_type_str<IntSet>().c_str())
      .def(nb::init<>())
      .def("insert",
          &IntSet::insert,
          "start"_a, "end"_a)
      .def("merge",
          &IntSet::merge,
          "other"_a)
      .def("covers",
          &IntSet::covers,
          "time"_a)
      .def("cover",
          &IntSet::cover)
      .def("__iter__", [](const IntSet& c) {
            return nb::make_iterator(c.begin(), c.end());
          }, nb::keep_alive<0, 1>())
      .def("__contains__",
          &IntSet::covers,
          "time"_a)
      .def(nb::self == nb::self)
      .def("__repr__", [](const IntSet& c) {
          return fmt::format("{}", c);
      });
  }
};

void declare_typed_interval_sets(nb::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_interval_set_types>,
      types::time_types>>{}(m);
}
