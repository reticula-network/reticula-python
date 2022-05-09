# Python bindings for [Reticula][reticula]

[reticula]: https://github.com/reticula-network/reticula

## Installation

The library offers pre-compiled Wheels for `manylinux2014` compatible systems.
That is, Linux systems with GNU C Library (glibc) version 2.17 and newer. The
library currently supports Python version 3.8, 3.9 and 3.10.

```bash
$ pip install reticula
```

### Installing from source
Alternatively you can install the library from source:

Clone the library:
```bash
$ git clone https://github.com/arashbm/reticula-python.git
```

Build the Wheel:
```bash
$ cd reticula-python
$ pip install .
```

Note that compiling source requires an unbelievable amount of RAM.

## Basic examples

Generate a random static network and investigate:
```python
import reticula as ret
state = ret.mersenne_twister(42)  # create a pseudorandom number generator
g = ret.random_gnp_graph[ret.int64](n=100, p=0.02, random_state=state)
print(g) # => <undirected_network[int64] with 100 verts and 110 edges>
print(g.vertices()) # => [0, 1, 2, 3, .... 99]
print(g.edges())
# => [undirected_edge[int64](0, 16), undirected_edge[int64](0, 20),
#       undirected_edge[int64](0, 31), undirected_edge[int64](0, 51),
#       ...]
print(ret.connected_components(g))
# => [<component[int64] of 1 nodes: {9}>,
#       <component[int64] of 1 node {33}>,
#       ...]
lcc = max(ret.connected_components(g), key=len)
print(lcc) # => <component[int64] of 93 nodes: {99, 96, 95, 94, ...}>
g2 = ret.vertiex_induced_subgraph(g, lcc)
print(g2) # => <undirected_network[int64] with 93 verts and 109 edges>
```
A more complete example of static network percolation analysis, running on
multiple threads, can be found in
[`examples/static_network_percolation/`](examples/static_network_percolation/)

Create a random fully-mixed temporal network and calculate simple
(unconstrained) reachability from node 0 at time 0 to all nodes and times.
```python
import reticula as ret
import ret.temporal_adjacency
state = ret.mersenne_twister(42)
g = ret.random_fully_mixed_temporal_network[int64](
        size=100, rate=0.01, max_t=1024, random_state=state)
adj = ret.temporal_adjacency.simple[
        ret.undirected_temporal_edge[ret.int64, ret.double]]()
cluster = ret.out_cluster(
        temporal_network=g, temporal_adjacency=adj, vertex=0, time=0.0)
print(cluster)
#  => <temporal_cluster[undirected_temporal_edge[int64, double],
#       simple[undirected_temporal_edge[int64, double]]] with volume 100
#       and lifetime (0 1.7976931348623157e+308]>
print(cluster.covers(vertex=12, time=100.0)) # => True

# Let's see all intervals where vert 15 is reachable from vert 0 at t=0.0:
print(list(cluster.interval_sets()[15]))
# => [(3.099055278145548, 1.7976931348623157e+308)]
```

Let's now try limited waiting-time (with dt = 5.0) reachability:
```python
import reticula as ret
import ret.temporal_adjacency
state = ret.mersenne_twister(42)
g = ret.random_fully_mixed_temporal_network[int64](
      size=100, rate=0.01, max_t=1024, random_state=state)
adj = ret.temporal_adjacency.limited_waiting_time[
      ret.undirected_temporal_edge[ret.int64, ret.double]](dt=5.0)
cluster = ret.out_cluster(
      temporal_network=g, temporal_adjacency=adj, vertex=0, time=0.0)
print(cluster)
# => <temporal_cluster[undirected_temporal_edge[int64, double],
#      limited_waiting_time[undirected_temporal_edge[int64, double]]] with
#      volume 100 and lifetime (0 1028.9972186553928]>
print(cluster.covers(vertex=15, time=16.0)) # => True
print(list(cluster.interval_sets()[15]))
# => [(3.099055278145548, 200.17866501023616),
#      (200.39858803326402, 337.96139372380003),
#      ...
#      (1017.5258263596586, 1028.9149586273347)]

# Total "human-hours" of reachability cluster
print(cluster.mass()) # => 101747.97444555275

# Survival time of the reachability cluster
print(cluster.lifetime()) # => (0.0, 1028.9972186553928)
```
