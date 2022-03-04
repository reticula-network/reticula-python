#include <random>

#include <pybind11/pybind11.h>

#include "type_str/random_state.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

void declare_random_states(py::module& m) {
  py::class_<std::mt19937_64>(m, python_type_str<std::mt19937_64>().c_str())
    .def(py::init([](){ return std::mt19937_64{std::random_device{}()}; }))
    .def(py::init<std::mt19937_64::result_type>(), "seed"_a);
}
