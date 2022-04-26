Network Types
=============

DAG support static and temporal networks involving two (dyadic) or more
(hypergraph) vertices in each event. The events can have an inherent
directionality and possibly a time delay.

It is also built with extensibility in mind. Adding a custom network type is, in
theory, as easy as introducing a new edge class in C++ that satisfies certain
concepts and defines certain type traits.

In this section, we will discuss the properties of the different edge and
network types.


General properties of networks
------------------------------

All network types are immutable. This means that all functions operating or
seemingly "modifying" networks actually return a modified **copy** of the input
networks.

The network types in python are based on statically typed C++. This imposes
restrictions on the type of vertices a network can carry. In C++, this is
indicated by template instantiation, e.g., the class
``dag::undirected_network<std::int64_t>`` indicates an undirected static network
with 64-bit signed integer vertices. The Python API, which by necessity has to
carry the same information, simulates this in a form similar to the existing
`type annotation`_ syntax: ``dag.undirected_network[dag.int64]``. Temporal
networks also need to know about the timestamp type that they should store. For
example ``dag.undirected_temporal_network[dag.int64, dag.double]`` marks a
continious time undirected temporal network with integer vertices.

If the type syntax looks verbose, remember that you can, and probably should,
assign a human-readable name to type in your code. This way you can avoid
repeating yourself without compromising on type safety:

.. code-block:: python

      network_type = dag.undirected_network[dag.int64]
      edge_type = network_type.edge_type()

      e1 = edge_type(1, 2)
      e2 = edge_type(3, 4)

      g1 = network_type(edges=[e1, e2], verts=[1, 2, 3, 4, 5])


.. _`type annotation`: https://docs.python.org/3/library/typing.html

Types
^^^^^

..
   A list of edge/network types, their properties (what they store)


Construction
^^^^^^^^^^^^

Networks can be initialised empty, by a list of edges, or by a list of edges and
vertices. In addition to explicitly stating a list of edge objects, you can use
tuples that implicitly convert to the correct edge type:

.. code-block:: python

      g1 = dag.undirected_network[dag.int64]() # an empty network
      g2 = dag.undirected_network[dag.int64](edges=[(1, 2), (2, 3)])
      g3 = dag.undirected_network[dag.int64](
               edges=[(1, 2), (2, 3)], verts=[1, 2, 3, 4, 5, 6])


This mimmics the C++ brace initialisation sysntax:

.. code-block:: c++

      dag::undirected_network<std::int64_t> g1; // an empty network
      dag::undirected_network<std::int64_t> g2({{1, 2}, {2, 3}});
      dag::undirected_network<std::int64_t> g3(
         {{1, 2}, {2, 3}},
         {1, 2, 3, 4, 5, 6});


The list of vertices is not required, but providing it can inform the network
that a vertice of with that name exists, even if there are not edges connected
to it.

.. note::

   The Python implicit conversion is currently sensetive to mixing different
   numeric types, e.g., if it is expecting a 2-tuple of double and you pass a
   2-tuple of integers, it cannot perform an implicit conversion. It is however
   okay to use a list instead of a tuple and vice versa.
