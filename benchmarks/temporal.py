import reticula as ret

import random


class Constrction:
    """
    Benchmarking the construction and basic operation of temporal networks.
    """

    def setup(self):
        self.n = 2**10
        rate = 4/self.n
        max_t = 32
        gen = ret.mersenne_twister(42)
        self.g = ret.random_fully_mixed_temporal_network[ret.int64](
            size=self.n, rate=rate, max_t=max_t, random_state=gen)
        self.verts = list(self.g.vertices())

        self.edges = list(self.g.edges())
        self.tuples = []
        for e in self.edges:
            verts = e.incident_verts()
            self.tuples.append((verts[0], verts[-1], e.cause_time()))

        rand = random.Random(42)
        self.shuffled_edges = rand.sample(self.edges, k=len(self.edges))
        self.shuffled_tuples = []
        for e in self.shuffled_edges:
            verts = e.incident_verts()
            if rand.random() > 0.5:
                self.shuffled_tuples.append(
                    (verts[0], verts[-1], e.cause_time()))
            else:
                self.shuffled_tuples.append(
                    (verts[-1], verts[0], e.cause_time()))

    def time_copy_construction(self):
        ret.undirected_temporal_network[ret.int64, ret.double](self.g)

    def time_tuple_construction(self):
        ret.undirected_temporal_network[ret.int64, ret.double](
            verts=self.verts, edges=self.tuples)

    def time_shuffled_tuple_construction(self):
        ret.undirected_temporal_network[ret.int64, ret.double](
            verts=self.verts, edges=self.shuffled_tuples)

    def time_edge_obj_construction(self):
        ret.undirected_temporal_network[ret.int64, ret.double](
            verts=self.verts, edges=self.edges)

    def time_shuffled_edge_obj_construction(self):
        ret.undirected_temporal_network[ret.int64, ret.double](
            verts=self.verts, edges=self.shuffled_edges)


class Algorithms:
    def setup(self):
        n = 2**11
        rate = 4/n
        max_t = 64
        gen = ret.mersenne_twister(42)
        self.g = ret.random_fully_mixed_temporal_network[ret.int64](
            size=n, rate=rate, max_t=max_t, random_state=gen)
        self.link = ret.undirected_edge[ret.int64](0, 1)

    def time_time_window(self):
        ret.time_window(self.g)

    def time_static_projection(self):
        ret.static_projection(self.g)

    def time_link_timeline(self):
        ret.link_timeline(self.g, self.link)

    def time_link_timelines(self):
        ret.link_timelines(self.g)


class Reachability:
    params = [
        ret.temporal_adjacency.simple[
            ret.undirected_temporal_edge[ret.int64, ret.double]](),
        ret.temporal_adjacency.limited_waiting_time[
            ret.undirected_temporal_edge[ret.int64, ret.double]](dt=1.0),
        ret.temporal_adjacency.exponential[
            ret.undirected_temporal_edge[ret.int64, ret.double]](
                rate=1.0, seed=12345)
    ]

    param_names = ["adjacency"]

    def setup(self, adj):
        gen = ret.mersenne_twister(42)

        max_t = 32
        small_n = 2**6
        small_rate = 4/small_n
        self.small_g = ret.random_fully_mixed_temporal_network[ret.int64](
            size=small_n, rate=small_rate, max_t=max_t, random_state=gen)

    def time_out_cluster(self, adj):
        ret.out_cluster(self.small_g, adj, vertex=0, time=0)

    def time_out_clusters(self, adj):
        ret.out_clusters(self.small_g, adj)

    def peakmem_out_clusters(self, adj):
        ret.out_clusters(self.small_g, adj)

    def time_out_cluster_sizes(self, adj):
        ret.out_cluster_sizes(self.small_g, adj)

    def peakmem_out_cluster_sizes(self, adj):
        ret.out_cluster_sizes(self.small_g, adj)

    def time_out_cluster_size_estimates(self, adj):
        ret.out_cluster_size_estimates(self.small_g, adj,
                                       time_resolution=0.5,
                                       seed=42)

    def peakmem_out_cluster_size_estimates(self, adj):
        ret.out_cluster_size_estimates(self.small_g, adj,
                                       time_resolution=0.5,
                                       seed=42)
