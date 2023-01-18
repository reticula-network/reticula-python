#include <pybind11/pybind11.h>

namespace py = pybind11;

void declare_typed_generators(py::module& m);
void declare_typed_random_networks(py::module& m);
void declare_typed_activation_networks(py::module& m);

void declare_typed_mrrm_algorithms(py::module& m);

void declare_generators(py::module& m) {
    declare_typed_generators(m);
    declare_typed_random_networks(m);
    declare_typed_activation_networks(m);

    py::module_ mrrm_m = m.def_submodule("microcanonical_reference_models");
    declare_typed_mrrm_algorithms(mrrm_m);
}
