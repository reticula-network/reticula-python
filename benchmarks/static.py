import reticula as ret

import random
import json
import pathlib


class Construction:
    """
    Benchmarking the construction and basic operation of static graphs.
    """

    def setup(self):
        self.n = 2**14
        k = 32
        self.g = ret.regular_ring_lattice[ret.int64](size=self.n, degree=k)
        self.verts = list(self.g.vertices())

        self.edges = list(self.g.edges())
        self.tuples = []
        for e in self.edges:
            verts = e.incident_verts()
            self.tuples.append((verts[0], verts[-1]))

        rand = random.Random(42)

        self.shuffled_edges = rand.sample(self.edges, k=len(self.edges))
        self.shuffled_tuples = []
        for e in self.shuffled_edges:
            verts = e.incident_verts()
            if rand.random() > 0.5:
                self.shuffled_tuples.append((verts[0], verts[-1]))
            else:
                self.shuffled_tuples.append((verts[-1], verts[0]))

    def time_copy_construction(self):
        ret.undirected_network[ret.int64](self.g)

    def time_tuple_construction(self):
        ret.undirected_network[ret.int64](
            verts=self.verts, edges=self.tuples)

    def time_shuffled_tuple_construction(self):
        ret.undirected_network[ret.int64](
            verts=self.verts, edges=self.shuffled_tuples)

    def time_edge_obj_construction(self):
        ret.undirected_network[ret.int64](
            verts=self.verts, edges=self.edges)

    def time_shuffled_edge_obj_construction(self):
        ret.undirected_network[ret.int64](
            verts=self.verts, edges=self.shuffled_edges)


class Graphicallity:
    def setup(self):
        base_path = pathlib.Path(__file__).parent
        with open(base_path / "ba_sequence.json") as f:
            self.ba_sequence = json.load(f)

    def time_is_graphic(self):
        ret.is_graphic(self.ba_sequence)


class Algorithms:
    def setup(self):
        self.n = 2**14
        k = 32
        self.g = ret.regular_ring_lattice[ret.int64](size=self.n, degree=k)
        self.g_isolated = ret.undirected_network[ret.int64](
            edges=[], verts=range(self.n))

    def time_degree(self):
        ret.degree(self.g, 12)

    def time_degree_sequence(self):
        ret.degree_sequence(self.g)

    def time_density(self):
        ret.density(self.g)

    def time_assortativity(self):
        ret.degree_assortativity(self.g)

    def time_attribute_assortativity_lambda(self):
        ret.attribute_assortativity(self.g, lambda x: x)

    def time_connected_component(self):
        ret.connected_component(self.g, 12)

    def time_connected_component_isolated(self):
        ret.connected_component(self.g_isolated, 12)

    def time_connected_components(self):
        ret.connected_components(self.g)

    def time_connected_components_isolated(self):
        ret.connected_components(self.g_isolated)

    def time_is_connected(self):
        ret.is_connected(self.g)

    def time_is_connected_isolated(self):
        ret.is_connected(self.g_isolated)

    def time_largest_connected_component(self):
        ret.largest_connected_component(self.g)

    def time_largest_connected_component_isolated(self):
        ret.largest_connected_component(self.g_isolated)

    def time_is_reachable(self):
        ret.is_reachable(self.g, 0, self.n//2)

    def time_is_reachable_isolated(self):
        ret.is_reachable(self.g_isolated, 0, self.n//2)

    def time_shortest_path_lengths_from(self):
        ret.shortest_path_lengths_from(self.g, 0)

    def time_shortest_path_lengths_to(self):
        ret.shortest_path_lengths_to(self.g, 0)


class RandomGraphs:
    def setup(self):
        self.gen = ret.mersenne_twister(42)
        self.ds = [4]*1000
        self.dds = [(4, 4)]*1000

    def time_barabasi_albert(self):
        ret.random_barabasi_albert_graph[ret.int64](
            n=4000, m=4, random_state=self.gen)

    def time_erdos_renyi(self):
        ret.random_gnp_graph[ret.int64](
            n=4000, p=0.001, random_state=self.gen)

    def time_directed_erdos_renyi(self):
        ret.random_directed_gnp_graph[ret.int64](
            n=4000, p=0.001, random_state=self.gen)

    def time_random_regular(self):
        ret.random_regular_graph[ret.int64](
            size=4000, degree=4, random_state=self.gen)

    def time_random_expected_degree_sequence_graph(self):
        ret.random_expected_degree_sequence_graph[ret.int64](
            weight_sequence=self.ds, random_state=self.gen)

    def time_random_directed_expected_degree_sequence_graph(self):
        ret.random_directed_expected_degree_sequence_graph[ret.int64](
            in_out_weight_sequence=self.dds, random_state=self.gen)

    def time_random_degree_sequence_graph(self):
        ret.random_degree_sequence_graph[ret.int64](
            degree_sequence=self.ds, random_state=self.gen)

    def time_random_directed_degree_sequence_graph(self):
        ret.random_directed_degree_sequence_graph[ret.int64](
            in_out_degree_sequence=self.dds, random_state=self.gen)
