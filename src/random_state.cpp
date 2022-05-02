#include <random>

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>

#include "type_str/random_state.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

void declare_random_states(nb::module_& m) {
  nb::class_<std::mt19937_64>(m, python_type_str<std::mt19937_64>().c_str())
    .def("__init__", [](){ return std::mt19937_64{std::random_device{}()}; })
    .def(nb::init<std::mt19937_64::result_type>(), "seed"_a);
}
