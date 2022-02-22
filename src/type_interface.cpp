#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;


template <typename T>
struct declare_scalar_types {
  void operator()(py::module &m) {
    py::class_<T>(m,
        type_str<T>{}().c_str())
      .def("__repr__", [](const T& a) {
        return fmt::format("{}", a);
      });
  }
};
