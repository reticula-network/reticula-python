#include <random>

#include <pybind11/pybind11.h>
#include <fmt/format.h>

#include "type_str/random_state.hpp"
#include "type_utils.hpp"
#include "metaclass.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

void declare_random_states(py::module& m) {
  auto metaclass = common_metaclass("random_state_metaclass");

  py::class_<std::mt19937_64>(
      m, python_type_str<std::mt19937_64>().c_str(),
      py::metaclass((PyObject*)metaclass))
    .def(py::init([](){ return std::mt19937_64{std::random_device{}()}; }),
          py::call_guard<py::gil_scoped_release>())
    .def(py::init<std::mt19937_64::result_type>(), "seed"_a,
          py::call_guard<py::gil_scoped_release>())
    .def_static("__class_repr__", []() {
      return fmt::format("<class '{}'>", type_str<std::mt19937_64>{}());
    });
}
