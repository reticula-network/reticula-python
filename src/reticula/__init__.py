import sys as _sys

from . import _reticula_ext
from .generic_attribute import generic_attribute as _generic_attribute
from . import temporal_adjacency
from . import microcanonical_reference_models

# import scalar type "tags"
from ._reticula_ext import (
        int64, double, string)

# patch the nb_type_0 metaclass to show the "correct" name for classes
setattr(type(int64), "__repr__", lambda kls: kls.__class_repr__())

_simple_vertex_types = set(_reticula_ext.types.simple_vertex_types)
pair = _generic_attribute(
        attr_prefix="pair",
        arg_names=("vertex_type", "vertex_type"),
        options={(i, j)
                 for i in _simple_vertex_types for j in _simple_vertex_types},
        function_module=_reticula_ext,
        api_module_name=__name__)

_static_edge_prefixes = [
        "directed_edge", "undirected_edge",
        "directed_hyperedge", "undirected_hyperedge"]

_integer_vertex_types = set(_reticula_ext.types.integer_vertex_types)
_all_vertex_types = set(_reticula_ext.types.vertex_types)

for _e in _static_edge_prefixes:
    setattr(_sys.modules[__name__],
            _e, _generic_attribute(
                attr_prefix=_e,
                arg_names=("vertex_type",),
                options={(t,) for t in _all_vertex_types},
                function_module=_reticula_ext,
                api_module_name=__name__))
    _n = _e[:-4] + "network"
    setattr(_sys.modules[__name__],
            _n, _generic_attribute(
                attr_prefix=_n,
                arg_names=("vertex_type",),
                options={(t,) for t in _all_vertex_types},
                function_module=_reticula_ext,
                api_module_name=__name__))

from ._reticula_ext import (
        mersenne_twister)

_integral_types = set(_reticula_ext.types.integral_types)
for _dist in [
        "geometric_distribution",
        "uniform_int_distribution"]:
    setattr(_sys.modules[__name__], _dist,
            _generic_attribute(
                attr_prefix=_dist,
                arg_names=("integral_type",),
                options={(t,) for t in _integral_types},
                function_module=_reticula_ext,
                api_module_name=__name__))

_floating_point_types = set(_reticula_ext.types.floating_point_types)
for _dist in [
        "exponential_distribution",
        "power_law_with_specified_mean",
        "residual_power_law_with_specified_mean",
        "hawkes_univariate_exponential",
        "uniform_real_distribution"]:
    setattr(_sys.modules[__name__], _dist,
            _generic_attribute(
                attr_prefix=_dist,
                arg_names=("floating_point_type",),
                options={(t,) for t in _floating_point_types},
                function_module=_reticula_ext,
                api_module_name=__name__))

delta_distribution = _generic_attribute(
        attr_prefix="delta_distribution",
        arg_names=("numeric_type",),
        options={(t,) for t in _integral_types | _floating_point_types},
        function_module=_reticula_ext,
        api_module_name=__name__)

_temporal_edge_prefixes = [
        "undirected_temporal_edge",
        "directed_temporal_edge",
        "directed_delayed_temporal_edge",
        "undirected_temporal_hyperedge",
        "directed_temporal_hyperedge",
        "directed_delayed_temporal_hyperedge"]

_time_types = set(_reticula_ext.types.time_types)

for _e in _temporal_edge_prefixes:
    setattr(_sys.modules[__name__],
            _e, _generic_attribute(
                attr_prefix=_e,
                arg_names=("vertex_type", "time_type"),
                options={(v, t)
                         for v in _all_vertex_types for t in _time_types},
                function_module=_reticula_ext,
                api_module_name=__name__))
    _n = _e[:-4] + "network"
    setattr(_sys.modules[__name__],
            _n, _generic_attribute(
                attr_prefix=_n,
                arg_names=("vertex_type", "time_type"),
                options={(v, t)
                         for v in _all_vertex_types for t in _time_types},
                function_module=_reticula_ext,
                api_module_name=__name__))


_vertex_generic_attrs = [
        "component", "component_size", "component_size_estimate"]
for _a in _vertex_generic_attrs:
    setattr(_sys.modules[__name__],
            _a, _generic_attribute(
                attr_prefix=_a,
                arg_names=("vertex_type",),
                options={(t,) for t in _all_vertex_types},
                function_module=_reticula_ext,
                api_module_name=__name__))


interval_set = _generic_attribute(
        attr_prefix="interval_set",
        arg_names=("time_type",),
        options={(t,) for t in _time_types},
        function_module=_reticula_ext,
        api_module_name=__name__)

implicit_event_graph = _generic_attribute(
        attr_prefix="implicit_event_graph",
        arg_names=("temporal_edge_type", "temporal_adjacency_type"),
        options=set(),
        function_module=_reticula_ext,
        api_module_name=__name__)


_all_edge_types = set(_reticula_ext.types.edge_types)
is_network_edge = _generic_attribute(
        attr_prefix="is_network_edge",
        arg_names=("edge_type",),
        options={(t,) for t in _all_edge_types},
        function_module=_reticula_ext,
        api_module_name=__name__)
is_static_edge = _generic_attribute(
        attr_prefix="is_static_edge",
        arg_names=("edge_type",),
        options=set((t,) for t in _all_edge_types),
        function_module=_reticula_ext,
        api_module_name=__name__)
is_temporal_edge = _generic_attribute(
        attr_prefix="is_temporal_edge",
        arg_names=("edge_type",),
        options={(t,) for t in _all_edge_types},
        function_module=_reticula_ext,
        api_module_name=__name__)
is_instantaneous = _generic_attribute(
        attr_prefix="is_instantaneous",
        arg_names=("edge_type",),
        options={(t,) for t in _all_edge_types},
        function_module=_reticula_ext,
        api_module_name=__name__)
is_undirected = _generic_attribute(
        attr_prefix="is_undirected",
        arg_names=("edge_type",),
        options={(t,) for t in _all_edge_types},
        function_module=_reticula_ext,
        api_module_name=__name__)
is_dyadic = _generic_attribute(
        attr_prefix="is_dyadic",
        arg_names=("edge_type",),
        options={(t,) for t in _all_edge_types},
        function_module=_reticula_ext,
        api_module_name=__name__)


_random_network_generic_attrs = [
        "random_gnp_graph",
        "random_directed_gnp_graph",
        "random_barabasi_albert_graph",
        "random_regular_graph",
        "random_expected_degree_sequence_graph",
        "random_expected_degree_sequence_hypergraph",
        "random_directed_expected_degree_sequence_graph",
        "random_directed_expected_degree_sequence_hypergraph",
        "random_uniform_hypergraph",
        "random_directed_uniform_hypergraph",
        "random_degree_sequence_graph",
        "random_directed_degree_sequence_graph",
        "random_fully_mixed_temporal_network",
        "random_directed_fully_mixed_temporal_network"]


for _a in _random_network_generic_attrs:
    setattr(_sys.modules[__name__],
            _a, _generic_attribute(
                attr_prefix=_a,
                arg_names=("integer_vertex_type",),
                options={(t,) for t in _integer_vertex_types},
                function_module=_reticula_ext,
                api_module_name=__name__))

_integer_vertex_generic_generators = [
        "square_grid_graph", "path_graph", "cycle_graph",
        "regular_ring_lattice", "complete_graph", "complete_directed_graph"]

for _a in _integer_vertex_generic_generators:
    setattr(_sys.modules[__name__],
            _a, _generic_attribute(
                attr_prefix=_a,
                arg_names=("integer_vertex_type",),
                options={(t,) for t in _integer_vertex_types},
                function_module=_reticula_ext,
                api_module_name=__name__))

from ._reticula_ext import (
    random_link_activation_temporal_network,
    random_node_activation_temporal_network)


_simple_edge_types = set()  # TODO
read_edgelist = _generic_attribute(
        attr_prefix="read_edgelist",
        arg_names=("edge_type",),
        options={(t,) for t in _simple_edge_types},
        function_module=_reticula_ext,
        api_module_name=__name__)
from ._reticula_ext import write_edgelist


from ._reticula_ext import (
        vertex_induced_subgraph, edge_induced_subgraph, graph_union,
        with_edges, with_vertices,
        without_edges, without_vertices,
        occupy_edges, occupy_vertices,
        uniformly_occupy_edges, uniformly_occupy_vertices,
        cartesian_product)

relabel_nodes = _generic_attribute(
        attr_prefix="relabel_nodes",
        arg_names=("integer_vertex_type",),
        options={(t,) for t in _integer_vertex_types},
        function_module=_reticula_ext,
        api_module_name=__name__)

from ._reticula_ext import (
        is_graphic, is_digraphic)

from ._reticula_ext import (
        in_degree, out_degree, incident_degree, degree,
        in_degree_sequence, out_degree_sequence, incident_degree_sequence,
        in_out_degree_pair_sequence, degree_sequence,
        edge_in_degree, edge_out_degree, edge_incident_degree, edge_degree,
        edge_in_degree_sequence, edge_out_degree_sequence,
        edge_incident_degree_sequence, edge_in_out_degree_pair_sequence,
        edge_degree_sequence,
        density, degree_assortativity, attribute_assortativity,
        in_in_degree_assortativity, in_out_degree_assortativity,
        out_out_degree_assortativity, out_in_degree_assortativity)

from ._reticula_ext import (
        is_acyclic, topological_order, out_component, out_components,
        out_component_sizes, out_component_size_estimates,
        in_component, in_components,
        in_component_sizes, in_component_size_estimates,
        is_weakly_connected, largest_weakly_connected_component,
        weakly_connected_component, weakly_connected_components,
        is_reachable, shortest_path_lengths_from, shortest_path_lengths_to)

from ._reticula_ext import (
        largest_connected_component,
        is_connected, connected_component, connected_components)

from ._reticula_ext import (
        time_window, cause_time_window, effect_time_window,
        event_graph, make_implicit_event_graph,
        out_cluster, out_clusters,
        out_cluster_sizes, out_cluster_size_estimates,
        in_cluster, in_clusters,
        in_cluster_sizes, in_cluster_size_estimates,
        static_projection, link_timeline, link_timelines)


def to_networkx(network, create_using=None):
    import networkx as _nx

    edge_type = network.edge_type()
    if not is_dyadic[edge_type]():
        raise ValueError("only dyadic networks can be translated into "
                         "NetworkX graphs")
    if is_temporal_edge[edge_type]():
        raise ValueError("only static networks can be translated into "
                         "NetworkX graphs")

    if create_using is None:
        if is_undirected[edge_type]():
            create_using = _nx.Graph()
        else:
            create_using = _nx.DiGraph()

    g = _nx.empty_graph(0, create_using)

    g.add_nodes_from(network.vertices())
    for e in network.edges():
        if is_undirected[edge_type]():
            verts = e.incident_verts()
            # support self-edges which have one incident vertices
            u, v = verts*2 if len(verts) == 1 else verts
            g.add_edge(u, v)
        else:
            g.add_edge(e.tail(), e.head())
    return g


def _from_networkx(g, vert_type):
    import networkx as _nx

    net_type = undirected_network[vert_type]
    if _nx.is_directed(g):
        net_type = directed_network[vert_type]
    edge_type = net_type.edge_type()
    verts = list(g.nodes())
    edges = [edge_type(i, j) for i, j in g.edges()]
    return net_type(edges=edges, verts=verts)


from functools import partial as _partial
for _vert_t in _all_vertex_types:
    setattr(_sys.modules[__name__], f"_from_networkx_{_vert_t.__name__}",
            _partial(_from_networkx, vert_type=_vert_t))
from_networkx = _generic_attribute(
        attr_prefix="_from_networkx",
        arg_names=("vertex_type",),
        options={(t,) for t in _all_vertex_types},
        function_module=_sys.modules[__name__],
        api_module_name=__name__)
