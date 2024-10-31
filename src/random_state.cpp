#include <random>

#include "bind_core.hpp"
#include <fmt/format.h>

#include "type_str/random_state.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

void declare_random_states(nb::module_& m) {
  nb::class_<std::mt19937_64>(m, python_type_str<std::mt19937_64>().c_str())
    .def("__init__", [](std::mt19937_64* t){
      new (t) std::mt19937_64{std::random_device{}()};
    }, nb::call_guard<nb::gil_scoped_release>())
    .def(nb::init<std::mt19937_64::result_type>(),
         "seed"_a, nb::call_guard<nb::gil_scoped_release>())
    .def("__copy__", [](const std::mt19937_64& self) {
        return std::mt19937_64(self);
    }).def("__deepcopy__", [](const std::mt19937_64& self, nb::dict) {
        return std::mt19937_64(self);
    }, "memo"_a)
    .def("__call__", [](std::mt19937_64& self) { return self(); })
    .def_static("__class_repr__", []() {
      return fmt::format("<class '{}'>", type_str<std::mt19937_64>{}());
    }).def_static("__class_name__", []() {
      return type_str<std::mt19937_64>{}();
    });
}
