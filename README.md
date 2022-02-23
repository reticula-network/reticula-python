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

## Basic use

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
