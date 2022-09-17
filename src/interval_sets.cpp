#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <reticula/intervals.hpp>

#include "type_str/intervals.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename TimeT>
struct declare_interval_set_types {
  void operator()(py::module &m) {
    using IntSet = reticula::interval_set<TimeT>;
    py::class_<IntSet>(m,
        python_type_str<IntSet>().c_str())
      .def(py::init<>(),
          py::call_guard<py::gil_scoped_release>())
      .def("insert",
          &IntSet::insert,
          "start"_a, "end"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("merge",
          &IntSet::merge,
          "other"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("covers",
          &IntSet::covers,
          "time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("cover",
          &IntSet::cover,
          py::call_guard<py::gil_scoped_release>())
      .def("__iter__", [](const IntSet& c) {
            return py::make_iterator(c.begin(), c.end());
          }, py::keep_alive<0, 1>())
      .def("__contains__",
          &IntSet::covers,
          "time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::self == py::self,
          py::call_guard<py::gil_scoped_release>())
      .def("__repr__", [](const IntSet& c) {
          return fmt::format("{}", c);
      })
      .def_static("value_type", []() {
        return types::handle_for<typename IntSet::ValueType>();
      });
  }
};

void declare_typed_interval_sets(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_interval_set_types>,
      types::time_types>>{}(m);
}
