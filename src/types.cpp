#include "bind_core.hpp"

namespace nb = nanobind;

void declare_typed_scalar(nb::module_& m);

void declare_random_states(nb::module_& m);
void declare_typed_distributions(nb::module_& m);
void declare_typed_interval_sets(nb::module_& m);

void declare_typed_static_edges(nb::module_& m);
void declare_typed_static_hyperedges(nb::module_& m);

void declare_typed_temporal_edges(nb::module_& m);
void declare_typed_temporal_hyperedges(nb::module_& m);

void declare_typed_networks(nb::module_& m);

void declare_typed_temporal_adjacency_class(nb::module_& m);

void declare_typed_components(nb::module_& m);
void declare_typed_temporal_clusters(nb::module_& m);

void declare_typed_implicit_event_graphs(nb::module_& m);
void declare_typed_implicit_event_graph_components(nb::module_& m);

void declare_type_lists(nb::module_& m);

void declare_types(nb::module_& m) {
    declare_typed_scalar(m);

    declare_random_states(m);
    declare_typed_distributions(m);
    declare_typed_interval_sets(m);

    declare_typed_temporal_edges(m);
    declare_typed_temporal_hyperedges(m);


    declare_typed_static_edges(m);
    declare_typed_static_hyperedges(m);

    declare_typed_networks(m);

    nb::module_ adj_m = m.def_submodule("temporal_adjacency");
    declare_typed_temporal_adjacency_class(adj_m);

    declare_typed_components(m);
    declare_typed_temporal_clusters(m);

    declare_typed_implicit_event_graphs(m);
    declare_typed_implicit_event_graph_components(m);

    nb::module_ types_m = m.def_submodule("types");
    declare_type_lists(types_m);
}
