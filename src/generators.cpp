#include "bind_core.hpp"

namespace nb = nanobind;

void declare_typed_generators(nb::module_& m);
void declare_typed_random_networks(nb::module_& m);
void declare_typed_activation_networks(nb::module_& m);

void declare_typed_mrrm_algorithms(nb::module_& m);

void declare_generators(nb::module_& m) {
    declare_typed_generators(m);
    declare_typed_random_networks(m);
    declare_typed_activation_networks(m);

    nb::module_ mrrm_m = m.def_submodule("microcanonical_reference_models");
    declare_typed_mrrm_algorithms(mrrm_m);
}
