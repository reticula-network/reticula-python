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

void declare_typed_components(py::module& m);
void declare_typed_temporal_clusters(py::module& m);

void declare_typed_implicit_event_graphs(py::module& m);
void declare_typed_implicit_event_graph_components(py::module& m);

void declare_type_lists(py::module& m);

void declare_types(py::module& m) {
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

    declare_typed_components(m);
    declare_typed_temporal_clusters(m);

    declare_typed_implicit_event_graphs(m);
    declare_typed_implicit_event_graph_components(m);

    py::module_ types_m = m.def_submodule("types");
    declare_type_lists(types_m);
}
