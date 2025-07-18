Modifying networks the immutable way
====================================

All Reticula networks are immutable.  Instead of changing a graph in place,
operations like adding or removing edges return a new object. This tutorial
demonstrates the basic ``with_*`` and ``without_*`` functions.

Adding edges
------------

Start with a simple cycle and add a few new links::

   >>> import reticula as ret
   >>> g = ret.cycle_graph[ret.int64](size=8)
   >>> extra = [(0, 5), (1, 6)]
   >>> g2 = ret.with_edges(g, extra)
   >>> len(g.edges()), len(g2.edges())
   (8, 10)

Because ``g`` is unchanged we can safely reuse it elsewhere.

Removing vertices
-----------------

Vertices can be removed in a similar fashion::

   >>> g3 = ret.without_vertices(g2, [0, 1])
   >>> len(g3.vertices())
   6

Any edges incident to the removed vertices disappear automatically.

Adding and removing multiple items at once is more efficient than
repeatedly calling these functions in a loop, so try to batch your
operations when possible.


Induced subgraphs
-----------------

A subset of a network can be created by selecting a set of vertices or edges,
using :py:func:`vertex_induced_subgraph` or :py:func:`edge_induced_subgraph`.
For example, to create a subgraph of the first five vertices::

   >>> g4 = ret.vertex_induced_subgraph(g, [0, 1, 2, 3, 4])
   >>> len(g4.vertices()), len(g4.edges())
   (5, 4)


Vertex and edge occupation
--------------------------

Another way to create a subset of the network is to prbabilistically keep a
fraction of the vertices or edges. This is useful for sampling large networks.
Inspired by the percolation literature, Reticula calls this process occupation.

Vertex or edge occupation is done with a uniform probability, using :py:func:`uniformly_occupy_edges` and :py:func:`uniformly_occupy_edges`::

   >>> gen = ret.mersenne_twister(42)
   >>> g5 = ret.uniformly_occupy_vertices(
   ...   g, occupation_prob=0.5, random_state=gen)
   >>> g5
   <undirected_network[int64] with 5 verts and 2 edges>

Similarly, the probability of keeping edges can be determined using a lambda
function. Here for example we set the odd vertices to be kept (occupied) at a
higher probability::

   >>> gen = ret.mersenne_twister(42)
   >>> g6 = ret.occupy_vertices(g,
   ...   lambda x: 0.3 if x%2 == 0 else 0.7,
   ...   random_state=gen)
   >>> g6
   <undirected_network[int64] with 5 verts and 3 edges>
