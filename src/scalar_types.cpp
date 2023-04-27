#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <fmt/format.h>

#include "type_str/scalars.hpp"
#include "type_utils.hpp"
#include "metaclass.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename T>
struct declare_scalar_types {
  void operator()(py::module &m, PyObject* metaclass) {
    py::class_<T>(m,
        python_type_str<T>().c_str(),
        py::metaclass(metaclass))
      .def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<T>{}());
      });
  }
};

void declare_typed_scalar(py::module& m) {
  auto metaclass = common_metaclass("_reticula_ext.scalar_metaclass");

  using scalar_types = types::unique<metal::join<
    types::time_types, types::simple_vert_types>>;

  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_scalar_types>,
      metal::join<scalar_types, types::pair_vert_types>>>{}(
          m, (PyObject*)metaclass);
}
