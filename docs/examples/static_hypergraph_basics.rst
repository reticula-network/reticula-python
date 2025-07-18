Getting started with hypergraphs
================================

Hypergraphs generalise standard graphs by allowing edges to contain any number
of vertices.  Reticula provides simple ways of generating and inspecting them.
Reticula provides both directed and undirected hypergraphs. Make sure you have
installed the library with ``pip install reticula`` and imported it as ``ret``::

   >>> import reticula as ret

Creating a random hypergraph
----------------------------

Let's stat with a simple example of a random hypergraph. The function :py:func:`random_uniform_hypergraph` generates a hypergraph with a given number of vertices, edges, and edge degree, each edge existing independently with a given probability. It requires a pseudo random number generator, which we create here with :py:func:`mersenne_twister`::

   >>> gen = ret.mersenne_twister(42)
   >>> h = ret.random_uniform_hypergraph[ret.int64](
   ...     size=100, edge_degree=3, edge_prob=0.01, random_state=gen)
   >>> h
   <undirected_hypergraph[int64] with 100 verts and 1659 edges>

Examining the structure
-----------------------

Edges and vertices are again simple Python lists::

   >>> h.vertices()[:5]
   [0, 1, 2, 3, 4]
   >>> h.edges()[:2]
   [undirected_hyperedge[int64]([0, 3, 96]), undirected_hyperedge[int64]([0, 4, 11])]
   >>> len(h.edges())
   1659

Hypergraph degrees count how many hyperedges a vertex belongs to::

   >>> ret.degree(h, 0)
   3

Since hypergraph h is undirected, the degree of a vertex is the same as its in- and
out-degree::

   >>> ret.in_degree(h, 0)
   3
   >>> ret.out_degree(h, 0)
   3
   >>> ret.incident_degree(h, 0)
   3

You can also probe each edge, for example to find out how many vertices it
contains, using :py:func:`edge_degree`. This is also known as the edge degree
or edge rank::

  >>> e = h.edges()[0]
  >>> e
  undirected_hyperedge[int64]([0, 3, 96])
  >>> ret.edge_degree(e)
  3

This also provices directed variants, but they are identical for undirected hypergraphs::
  >>> ret.in_edge_degree(e)
  3
  >>> ret.out_edge_degree(e)
  3

Hyperedge mutators and mutated vertices work similarly to undirected edges in
dyadic networks. The mutator vertices are those that can change the state of
the other vertices through the hyperedge, while the mutated vertices are those
whose state can change because of the mutators. For undirected hyperedges, all
vertices incident to the hyperedge can act as mutators or mutated vertices::

   >>> e.mutator_verts()
   [0, 3, 96]
   >>> e.mutated_verts()
   [0, 3, 96]
   >>> e.incident_verts()
   [0, 3, 96]

For directed hyperedges, the mutator and mutated vertices can be different::

   >>> e = ret.directed_hyperedge[int64]([1, 2, 3], [4, 5, 6])
   >>> e.mutator_verts()
   [1, 2, 3]
   >>> e.tails()
   [1, 2, 3]

   >>> e.mutated_verts()
   [4, 5, 6]
   >>> e.heads()
   [4, 5, 6]

   >>> e.incident_verts()
   [1, 2, 3, 4, 5, 6]


Connected components
--------------------

Connected components work exactly the same as for dyadic static graphs::

   >>> comps = ret.connected_components(h)
   >>> comps
   [<component[int64] of 100 nodes: {99, 98, 97, 96, 95, ...})>]
   >>> len(comps)
   1
