# Python bindings for DAG

## Instaling from source

Clone the library:
```bash
$ git clone https://github.com/arashbm/dag-python.git
```

Build the Wheel:
```bash
$ cd dag-python
$ python setup.py bdist_wheel -- -- -j 3
```

There should be Wheel (`.whl`) fil in a newly created `dist/` directory:
```bash
$ ls dist
dag-X.X.X-XXX.whl
$ pip install dist/dag-X.X.X-XXX.whl
```
It might be helpful to use the `--force-reinstall` flag for pip during
development.

## Basic examples

Generate a random static network and investigate:
```python
>>> import dag
>>> state = dag.mersenne_twister(42)  # create a pseudorandom number generator
>>> g = dag.random_gnp_graph[dag.int64](n=100, p=0.02, random_state=state)
>>> g
<dag.undirected_network[dag.int64] with 100 verts and 110 edges>
>>> g.vertices()
[0, 1, 2, 3, .... 99]
>>> g.edges()
[dag.undirected_edge[dag.int64](0, 16), dag.undirected_edge[dag.int64](0, 20),
  dag.undirected_edge[dag.int64](0, 31), dag.undirected_edge[dag.int64](0, 51),
  ...]
>>> dag.connected_components(g)
[<dag.component[dag.int64] of 1 nodes: {9}>,
  <dag.component[dag.int64] of 1 node {33}>,
  ...]
>>> lcc = max(dag.connected_components(g), key=len)
>>> lcc
<dag.component[dag.int64] of 93 nodes: {99, 96, 95, 94, ...}>
>>> g2 = dag.vertiex_induced_subgraph(g, lcc)
>>> g2
<dag.undirected_network[dag.int64] with 93 verts and 109 edges>
```
A more complete example of static network percolation analysis, running on
multiple threads, can be found in
[`examples/static_network_percolation/`](examples/static_network_percolation/)

Create a random fully-mixed temporal network and calculate simple
(unconstrained) reachability from node 0 at time 0 to all nodes and times.
```python
>>> import dag
>>> import dag.temporal_adjacency
>>> state = dag.mersenne_twister(42)
>>> g = dag.random_fully_mixed_temporal_network[dag.int64](
...       size=100, rate=0.01, max_t=1024, random_state=state)
>>> adj = dag.temporal_adjacency.simple[
...       dag.undirected_temporal_edge[dag.int64, dag.double]]()
>>> cluster = dag.out_cluster(
...       temporal_network=g, temporal_adjacency=adj, vertex=0, time=0.0)
>>> cluster
<dag.temporal_cluster[undirected_temporal_edge[int64, double],
  simple[dag.undirected_temporal_edge[dag.int64, dag.double]]] with volume 100
  and lifetime (0 1.7976931348623157e+308]>
>>> cluster.covers(vertex=12, time=100.0)
True
>>> # Let's see all intervals where vert 15 is reachable from vert 0 at t=0.0:
>>> list(cluster.interval_sets()[15])
[(3.099055278145548, 1.7976931348623157e+308)]
```

Let's now try limited waiting-time (with dt = 5.0) reachability:
```python
>>> import dag
>>> import dag.temporal_adjacency
>>> state = dag.mersenne_twister(42)
>>> g = dag.random_fully_mixed_temporal_network[dag.int64](
...       size=100, rate=0.01, max_t=1024, random_state=state)
>>> adj = dag.temporal_adjacency.limited_waiting_time[
...       dag.undirected_temporal_edge[dag.int64, dag.double]](dt=5.0)
>>> cluster = dag.out_cluster(
...       temporal_network=g, temporal_adjacency=adj, vertex=0, time=0.0)
>>> cluster
<dag.temporal_cluster[undirected_temporal_edge[int64, double],
  limited_waiting_time[undirected_temporal_edge[int64, double]]] with volume
  100 and lifetime (0 1028.9972186553928]>
>>> cluster.covers(vertex=15, time=16.0)
True
>>> list(cluster.interval_sets()[15])
[(3.099055278145548, 200.17866501023616),
  (200.39858803326402, 337.96139372380003),
  ...
  (1017.5258263596586, 1028.9149586273347)]
>>> cluster.mass()  # total "human-hours" of reachability
101747.97444555275
>>> cluster.lifetime()
(0.0, 1028.9972186553928)
```
