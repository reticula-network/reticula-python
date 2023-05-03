#include "bind_core.hpp"

namespace nb = nanobind;

void declare_types(nb::module_& m);
void declare_generators(nb::module_& m);
void declare_io(nb::module_& m);
void declare_operations(nb::module_& m);
void declare_algorithms(nb::module_& m);

NB_MODULE(_reticula_ext, m) {
  declare_types(m);
  declare_generators(m);
  declare_io(m);
  declare_operations(m);
  declare_algorithms(m);
}
