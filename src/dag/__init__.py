import sys
import itertools

from . import dag_ext

__all__ = ["temporal_adjacency"]

class generic_attribute:
    def __init__(self, attr_prefix, choices, module=dag_ext):
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
        for i, k, cs in zip(itertools.count(), keys, self.choices):
            if not cs or k in cs:
                attr_name += "_" + k.__name__
            else:
                raise AttributeError(f"Template type {i} ({k}) is not a valid "
                        "choise. Valid options are: {cs}")
        return self.module.__getattribute__(attr_name)


static_edge_prefixes = [
        "directed_edge", "undirected_edge",
        "directed_hyperedge", "undirected_hyperedge"]

integer_vert_types = set()
non_integer_vert_types = set()
vert_types = non_integer_vert_types | integer_vert_types

for e in static_edge_prefixes:
    setattr(sys.modules[__name__], e, generic_attribute(e, [vert_types]))
    n = e[:-4] + "network"
    setattr(sys.modules[__name__], n, generic_attribute(n, [vert_types]))

temporal_edge_prefixes = [
        "undirected_temporal_edge",
        "directed_temporal_edge",
        "directed_delayed_temporal_edge",
        "undirected_temporal_hyperedge",
        "directed_temporal_hyperedge",
        "directed_delayed_temporal_hyperedge"]

time_types = set()

for e in temporal_edge_prefixes:
    setattr(sys.modules[__name__],
            e, generic_attribute(e, [vert_types, time_types]))
    n = e[:-4] + "network"
    setattr(sys.modules[__name__],
            n, generic_attribute(n, [vert_types, time_types]))


vertex_generic_attrs = [
        "component", "component_size", "component_size_estimate"]
for a in vertex_generic_attrs:
    setattr(sys.modules[__name__],  a, generic_attribute(a, [vert_types]))


integer_vertex_generic_attrs = [
        "relabel_nodes", "square_grid_graph", "path_graph", "cycle_graph",
        "regular_ring_lattice", "complete_graph", "complete_directed_graph"]

for a in integer_vertex_generic_attrs:
    setattr(sys.modules[__name__],
            a, generic_attribute(a, [integer_vert_types]))

interval_set = generic_attribute("interval_set", [time_types])

random_network_generic_attrs = [
        "random_gnp_graph",
        "random_barabasi_albert_graph",
        "random_regular_graph",
        "random_expected_degree_sequence_graph",
        "random_directed_expected_degree_sequence_graph",
        "random_degree_sequence_graph",
        "random_directed_degree_sequence_graph",
        "random_fully_mixed_temporal_network",
        "random_directed_fully_mixed_temporal_network"]
for a in random_network_generic_attrs:
    setattr(sys.modules[__name__],
            a, generic_attribute(a, [integer_vert_types]))

# import overloaded funcitons
from .dag_ext import (
        cartesian_product, is_graphic, is_digraphic)

from .dag_ext import (
        vertex_induced_subgraph, edge_induced_subgraph, graph_union, density)

from .dag_ext import (
        is_acyclic, topological_order, out_component, out_components,
        out_component_sizes, out_component_size_estimates,
        in_component, in_components,
        in_component_sizes, in_component_size_estimates,
        weakly_connected_component, weakly_connected_components,
        is_reachable)

from .dag_ext import (
        is_connected, connected_component, connected_components)

from .dag_ext import (
        time_window, cause_time_window, effect_time_window, event_graph,
        out_cluster, out_clusters,
        out_cluster_sizes, out_cluster_size_estimates,
        in_cluster, in_clusters,
        in_cluster_sizes, in_cluster_size_estimates,
        static_projection, link_timeline, link_timelines)

from .dag_ext import (
        mersenne_twister)

# import scalar type "tags"
from .dag_ext import (
        int64, double, string)
