#include <pybind11/pybind11.h>

namespace py = pybind11;

void declare_types(py::module& m);
void declare_generators(py::module& m);
void declare_io(py::module& m);
void declare_operations(py::module& m);
void declare_algorithms(py::module& m);

PYBIND11_MODULE(_reticula_ext, m) {
  declare_types(m);
  declare_generators(m);
  declare_io(m);
  declare_operations(m);
  declare_algorithms(m);
}
