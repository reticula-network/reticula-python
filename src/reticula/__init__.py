import sys as _sys
import itertools as _itertools

from . import reticula_ext as _reticula_ext

__all__ = ["temporal_adjacency", "microcanonical_reference_models"]

class _generic_attribute:
    def __init__(self, attr_prefix, choices, module=_reticula_ext):
        self.choices = choices
        self.attr_prefix = attr_prefix
        self.module = module
    def __getitem__(self, keys):
        if len(self.choices) == 1:
            keys = (keys,)
        if len(keys) != len(self.choices):
            raise AttributeError(f"Wrong number of type templates: expected "
                    f"{len(self.choices)} template types but received "
                    f"{len(keys)}")
        attr_name = str(self.attr_prefix)
        for i, k, cs in zip(_itertools.count(), keys, self.choices):
            if not cs or k in cs:
                attr_name += "_" + k.__name__
            else:
                raise AttributeError(f"Template type {i} ({k}) is not a valid "
                        "choise. Valid options are: {cs}")
        return self.module.__getattribute__(attr_name)
    def __call__(self, *args, **kwargs):
        raise TypeError(f"No type information was paased to a generic function "
                f"or type. This usually means that you forgot to add square "
                f"brackets and type information before parentheses, e.g. "
                f"`{__name__}.{self.attr_prefix}[types...]` "
                f"Valid options are: {self.choices}")


_static_edge_prefixes = [
        "directed_edge", "undirected_edge",
        "directed_hyperedge", "undirected_hyperedge"]

_integer_vert_types = set()
_non_integer_vert_types = set()
_vert_types = _non_integer_vert_types | _integer_vert_types

for _e in _static_edge_prefixes:
    setattr(_sys.modules[__name__],
            _e, _generic_attribute(_e, [_vert_types]))
    _n = _e[:-4] + "network"
    setattr(_sys.modules[__name__],
            _n, _generic_attribute(_n, [_vert_types]))

_temporal_edge_prefixes = [
        "undirected_temporal_edge",
        "directed_temporal_edge",
        "directed_delayed_temporal_edge",
        "undirected_temporal_hyperedge",
        "directed_temporal_hyperedge",
        "directed_delayed_temporal_hyperedge"]

_time_types = set()

for _e in _temporal_edge_prefixes:
    setattr(_sys.modules[__name__],
            _e, _generic_attribute(_e, [_vert_types, _time_types]))
    _n = _e[:-4] + "network"
    setattr(_sys.modules[__name__],
            _n, _generic_attribute(_n, [_vert_types, _time_types]))


_vertex_generic_attrs = [
        "component", "component_size", "component_size_estimate"]
for _a in _vertex_generic_attrs:
    setattr(_sys.modules[__name__],
            _a, _generic_attribute(_a, [_vert_types]))


_integer_vertex_generic_attrs = [
        "relabel_nodes", "square_grid_graph", "path_graph", "cycle_graph",
        "regular_ring_lattice", "complete_graph", "complete_directed_graph"]

for _a in _integer_vertex_generic_attrs:
    setattr(_sys.modules[__name__],
            _a, _generic_attribute(_a, [_integer_vert_types]))

interval_set = _generic_attribute("interval_set", [_time_types])

_random_network_generic_attrs = [
        "random_gnp_graph",
        "random_barabasi_albert_graph",
        "random_regular_graph",
        "random_expected_degree_sequence_graph",
        "random_directed_expected_degree_sequence_graph",
        "random_degree_sequence_graph",
        "random_directed_degree_sequence_graph",
        "random_fully_mixed_temporal_network",
        "random_directed_fully_mixed_temporal_network"]
for _a in _random_network_generic_attrs:
    setattr(_sys.modules[__name__],
            _a, _generic_attribute(_a, [_integer_vert_types]))

_simple_edge_types = set()
read_edgelist = _generic_attribute("read_edgelist", [_simple_edge_types])

_all_edge_types = set()
is_network_edge = _generic_attribute("is_network_edge", [_all_edge_types])
is_static_edge = _generic_attribute("is_static_edge", [_all_edge_types])
is_temporal_edge = _generic_attribute("is_temporal_edge", [_all_edge_types])
is_instantaneous = _generic_attribute("is_instantaneous", [_all_edge_types])
is_undirected = _generic_attribute("is_undirected", [_all_edge_types])
is_dyadic = _generic_attribute("is_dyadic", [_all_edge_types])

# import overloaded funcitons
from .reticula_ext import (
        cartesian_product, is_graphic, is_digraphic)

from .reticula_ext import (
        vertex_induced_subgraph, edge_induced_subgraph, graph_union,
        with_edges, with_vertices, density)

from .reticula_ext import (
        is_acyclic, topological_order, out_component, out_components,
        out_component_sizes, out_component_size_estimates,
        in_component, in_components,
        in_component_sizes, in_component_size_estimates,
        weakly_connected_component, weakly_connected_components,
        is_reachable)

from .reticula_ext import (
        is_connected, connected_component, connected_components)

from .reticula_ext import (
        time_window, cause_time_window, effect_time_window, event_graph,
        out_cluster, out_clusters,
        out_cluster_sizes, out_cluster_size_estimates,
        in_cluster, in_clusters,
        in_cluster_sizes, in_cluster_size_estimates,
        static_projection, link_timeline, link_timelines)

from .reticula_ext import (
        mersenne_twister)

# import scalar type "tags"
from .reticula_ext import (
        int64, double, string)

_simple_vert_types = set()
pair = _generic_attribute("pair", [_simple_vert_types, _simple_vert_types])

def to_nx(network, create_using=None):
    edge_type = network.edge_type()
    if not is_dyadic[edge_type]():
        raise ValueError("only dyadic networks can be tranlated into NetworkX "
                "graphs")
    if is_temporal_edge[edge_type]():
        raise ValueError("only static networks can be tranlated into NetworkX "
                "graphs")

    import networkx as nx
    if create_using is None:
        if is_undirected[edge_type]():
            create_using = nx.Graph()
        else:
            create_using = nx.DiGraph()

    g = nx.empty_graph(0, create_using)

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
