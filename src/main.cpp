#include <string>
#include <filesystem>

#include <nanobind/nanobind.h>
#include <fmt/format.h>

namespace nb = nanobind;

void declare_typed_scalar(nb::module_& m);

void declare_random_states(nb::module_& m);
void declare_typed_interval_sets(nb::module_& m);

void declare_typed_static_edges(nb::module_& m);
void declare_typed_static_hyperedges(nb::module_& m);

void declare_typed_temporal_edges(nb::module_& m);
void declare_typed_temporal_hyperedges(nb::module_& m);

void declare_typed_networks(nb::module_& m);

void declare_typed_temporal_adjacency_class(nb::module_& m);

void declare_typed_implicit_event_graphs(nb::module_& m);
void declare_typed_implicit_event_graph_components(nb::module_& m);

void declare_typed_generators(nb::module_& m);
void declare_typed_random_networks(nb::module_& m);

void declare_typed_components(nb::module_& m);
void declare_typed_component_containers(nb::module_& m);
void declare_typed_temporal_clusters(nb::module_& m);
void declare_typed_temporal_cluster_containers(nb::module_& m);

void declare_typed_algorithms(nb::module_& m);

void declare_typed_mrrm_algorithms(nb::module_& m);

void declare_typed_io_functions(nb::module_& m);

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

NB_MODULE(dag_ext, m) {
    declare_typed_scalar(m);

    declare_random_states(m);
    declare_typed_interval_sets(m);

    declare_typed_temporal_edges(m);
    declare_typed_temporal_hyperedges(m);


    declare_typed_static_edges(m);
    declare_typed_static_hyperedges(m);

    declare_typed_networks(m);

    nb::module_ adj_m = m.def_submodule("temporal_adjacency");
    declare_typed_temporal_adjacency_class(adj_m);

    declare_typed_implicit_event_graphs(m);
    declare_typed_implicit_event_graph_components(m);

    declare_typed_generators(m);
    declare_typed_random_networks(m);

    declare_typed_components(m);
    declare_typed_component_containers(m);
    declare_typed_temporal_clusters(m);
    declare_typed_temporal_cluster_containers(m);

    declare_typed_algorithms(m);

    nb::module_ mrrm_m = m.def_submodule("microcanonical_reference_models");
    declare_typed_mrrm_algorithms(mrrm_m);

    declare_typed_io_functions(m);
#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
