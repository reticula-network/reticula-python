#include <pybind11/pybind11.h>

namespace py = pybind11;

void declare_typed_scalar(py::module& m);

void declare_random_states(py::module& m);
void declare_typed_distributions(py::module& m);
void declare_typed_interval_sets(py::module& m);

void declare_typed_static_edges(py::module& m);
void declare_typed_static_hyperedges(py::module& m);

void declare_typed_temporal_edges(py::module& m);
void declare_typed_temporal_hyperedges(py::module& m);

void declare_typed_networks(py::module& m);

void declare_typed_temporal_adjacency_class(py::module& m);

void declare_typed_implicit_event_graphs(py::module& m);
void declare_typed_implicit_event_graph_components(py::module& m);

void declare_typed_generators(py::module& m);
void declare_typed_random_networks(py::module& m);
void declare_typed_activation_networks(py::module& m);

void declare_typed_components(py::module& m);
void declare_typed_temporal_clusters(py::module& m);

void declare_typed_algorithms(py::module& m);

void declare_typed_mrrm_algorithms(py::module& m);

void declare_typed_io_functions(py::module& m);

void declare_type_lists(py::module& m);

PYBIND11_MODULE(reticula_ext, m) {
    declare_typed_scalar(m);

    declare_random_states(m);
    declare_typed_distributions(m);
    declare_typed_interval_sets(m);

    declare_typed_temporal_edges(m);
    declare_typed_temporal_hyperedges(m);


    declare_typed_static_edges(m);
    declare_typed_static_hyperedges(m);

    declare_typed_networks(m);

    py::module_ adj_m = m.def_submodule("temporal_adjacency");
    declare_typed_temporal_adjacency_class(adj_m);

    declare_typed_implicit_event_graphs(m);
    declare_typed_implicit_event_graph_components(m);

    declare_typed_generators(m);
    declare_typed_random_networks(m);
    declare_typed_activation_networks(m);

    declare_typed_components(m);
    declare_typed_temporal_clusters(m);

    declare_typed_algorithms(m);

    py::module_ mrrm_m = m.def_submodule("microcanonical_reference_models");
    declare_typed_mrrm_algorithms(mrrm_m);

    declare_typed_io_functions(m);

    py::module_ types_m = m.def_submodule("types");
    declare_type_lists(types_m);
}
