Basic static network exploration
================================

This tutorial introduces a few simple functions for static undirected networks.
All examples assume that you already installed Reticula with ``pip install
reticula`` and have ``ret`` imported as the usual alias::

   >>> import reticula as ret

Generating a random network
---------------------------

We start by creating a random :math:`G(n,p)` network.  The function
:py:func:`random_gnp_graph` requires a pseudo random number generator, created
here with :py:func:`mersenne_twister`::

   >>> gen = ret.mersenne_twister(42)
   >>> g = ret.random_gnp_graph[ret.int64](n=100, p=0.02, random_state=gen)
   >>> g
   <undirected_network[int64] with 100 verts and 110 edges>

Inspecting the network
----------------------

The vertices and edges can be retrieved as Python lists::

   >>> g.vertices()[:5]
   [0, 1, 2, 3, 4]
   >>> g.edges()[:3]
   [undirected_edge[int64](0, 16), undirected_edge[int64](0, 20), ...]

Several helper functions report basic properties such as the number of vertices
or edges and the network density::

   >>> len(g.vertices())
   100
   >>> len(g.edges())
   110
   >>> ret.density(g)
   0.022223

You can probe the edges of the network, for example to find out how which nodes
are connected by a specific edge.

Mutator vertices are those vertices that can change the state of the other
nodes through a specific edge, and mutated vertices are those whose internal
state can change because of mutators. For undirected_network, all nodes
incident to an edge can act as mutators or mutated vertices::

   >>> e = g.edges()[0]
   >>> e
   undirected_edge[int64](0, 16)
   >>> e.mutator_verts()
   [0, 16]
   >>> e.mutated_verts()
   [0, 16]
   >>> e.incident_verts()
   [0, 16]

This is not the case for directed networks, where the mutator and mutated
vertices can be different.

   >>> e = ret.directed_edge[int64](0, 16)
   >>> e
   directed_edge[int64](0, 16)
   >>> e.mutator_verts()
   [0]
   >>> e.tail()
   0
   >>> e.mutated_verts()
   [16]
   >>> e.head()
   16
   >>> e.incident_verts()
   [0, 16]


Connected components
--------------------

The function :py:func:`connected_components` returns all components of an
undirected network::

   >>> comps = ret.connected_components(g)
   >>> lcc = max(comps, key=len)
   >>> lcc
   <component[int64] of 93 nodes: {99, 96, 95, 94, 92, 91, 90, 89, 88, 87, ...})>
   >>> len(lcc)
   93

If you are only interested in the largest component, you can directly use
:py:func:`largest_connected_component`::

  >> lcc = ret.largest_connected_component(g)
  >> lcc
  <component[int64] of 93 nodes: {99, 96, 95, 94, 92, 91, 90, 89, 88, 87, ...})>


Degrees and neighbourhoods
--------------------------

Degree information for each vertex is accessible via :py:func:`degree`::

   >>> ret.degree(g, 0)
   4

Since graph g is undirected, the degree of a vertex is the same as its in- and
out-degree::

   >>> ret.in_degree(g, 0)
   4
   >>> ret.out_degree(g, 0)
   4
   >>> ret.incident_degree(g, 0)
   4

You can also directly generate the degree sequence of the network, using
:py:func:`degree_sequence`::

   >>> ret.degree_sequence(g)
   [4, 1, 0, 6, 1, 2, 1, 0, ...]
   >>> ret.in_degree_sequence(g)
   [4, 1, 0, 6, 1, 2, 1, 0, ...]
   >>> ret.out_degree_sequence(g)
   [4, 1, 0, 6, 1, 2, 1, 0, ...]
   >>> ret.incident_degree_sequence(g)
   [4, 1, 0, 6, 1, 2, 1, 0, ...]

You can get a list of neighbours of a node::

   >>> g.neighbours(0)
   [20, 51, 31, 16]


Similar to before, you can also get the successors and predecessors, the
directed in- and out-neighbours, of a vertex::

   >>> g.successors(0)
   [20, 51, 31, 16]
   >>> g.prdecessors(0)
   [20, 51, 31, 16]


These simple building blocks will let you start exploring static networks in
Reticula.
