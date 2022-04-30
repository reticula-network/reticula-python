Networks and network types
==========================

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

The network and edge types in python are based on statically typed C++ classes.
This imposes restrictions on the type of vertices or timestamps a network can
store. In C++, this is indicated by template instantiation, e.g., the class
:cpp:`dag::undirected_network<std::int64_t>` indicates an undirected static
network with 64-bit signed integer vertices. The Python API, which by necessity
has to carry the same information, simulates this in a form similar to the
existing `type annotation`_ syntax: :py:`dag.undirected_network[dag.int64]`.
Temporal networks also need to know about the time type that they should store.
For example :py:`dag.undirected_temporal_network[dag.int64, dag.double]`
marks a continuous time undirected temporal network with integer vertices.

If the type syntax looks verbose, remember that you can, and probably should,
assign a human-readable name to repeatedly-used types in your code. This way you
can avoid repeating yourself without compromising on type safety:

.. code-block:: python

      network_type = dag.undirected_network[dag.int64]
      edge_type = network_type.edge_type()

      e1 = edge_type(1, 2)
      e2 = edge_type(3, 4)

      g1 = network_type(edges=[e1, e2], verts=[1, 2, 3, 4, 5])

.. note:: It's probably a good idea to use more **meaningful** and **specific**
  names than :py:`edge_type` and :py:`network_type`. For example, a study on
  scientific citation temporal networks can use :py:`citation_event` for
  temporal edges and :py:`citation_network` for the network type.

.. _`type annotation`: https://docs.python.org/3/library/typing.html


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


This mimics the C++ brace initialisation syntax:

.. code-block:: cpp

      dag::undirected_network<std::int64_t> g1; // an empty network
      dag::undirected_network<std::int64_t> g2({{1, 2}, {2, 3}});
      dag::undirected_network<std::int64_t> g3(
         {{1, 2}, {2, 3}},
         {1, 2, 3, 4, 5, 6});


The list of vertices is not required, but providing it can inform the network
that a vertex of with that name exists, even if there are not edges connected
to it.

.. note::
   The Python implicit conversion is currently sensetive to mixing different
   numeric types, e.g., if it is expecting a 2-tuple of double and you pass a
   2-tuple of integers, it cannot perform an implicit conversion. It is however
   okay to use a list instead of a tuple and vice versa.


Edges and vertices
^^^^^^^^^^^^^^^^^^

Edges and vertices are accessible through member functions of the same name.

.. code-block:: python

      g3.edges() # list of two edges
      g3.vertices() # list six vertices

You can also get the network edges sorted by :cpp:`operator<`
(:py:`operator.__lt__` in Python) or :cpp:func:`dag::effect_lt`
(:py:func:`dag.effect_lt`) through functions `edges_cause` and `edges_effect`
member functions. In a temporal network the result of the former will be sorted
by cause time and the latter by effect time of the events. In static networks
they return the same output.

Incident edges
^^^^^^^^^^^^^^

Successors, predecessors and neighbours
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Vertex degree
^^^^^^^^^^^^^

..
  in hypergraphs and temporal networks



Network types
-------------

.. cpp:class:: template <dag::network_edge EdgeT> dag::network<EdgeT>


Undirected static networks
^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT> \
   dag::undirected_network<VertT>

.. py:class:: dag.undirected_network[vertex_type]


Directed static networks
^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT> \
   dag::directed_network<VertT>

.. py:class:: dag.directed_network[vertex_type]


Undirected static hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT> \
   dag::undirected_hypernetwork<VertT>

.. py:class:: dag.undirected_hypernetwork[vertex_type]


Directed static hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT> \
   dag::directed_hypernetwork<VertT>

.. py:class:: dag.directed_hypernetwork[vertex_type]


Directed temporal networks
^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT, typename TimeT> \
   dag::undirected_temporal_network<VertT, TimeT>

.. py:class:: dag.undirected_temporal_network[vertex_type, time_type]

Directed temporal networks
^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT, typename TimeT> \
   dag::directed_temporal_network<VertT, TimeT>

.. py:class:: dag.directed_temporal_network[vertex_type, time_type]


Directed delayed temporal networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT, typename TimeT> \
   dag::directed_delayed_temporal_network<VertT, TimeT>

.. py:class:: dag.directed_delayed_temporal_network[vertex_type, time_type]


Undirected temporal hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT, typename TimeT> \
   dag::undirected_temporal_hypernetwork<VertT, TimeT>

.. py:class:: dag.undirected_temporal_hypernetwork[vertex_type, time_type]

Directed temporal hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT, typename TimeT> \
   dag::directed_temporal_hypernetwork<VertT, TimeT>

.. py:class:: dag.directed_temporal_hypernetwork[vertex_type, time_type]

Directed delayed temporal hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <dag::network_vertex VertT, typename TimeT> \
   dag::directed_delayed_temporal_hypernetwork<VertT, TimeT>

.. py:class:: dag.directed_delayed_temporal_hypernetwork[\
   vertex_type, time_type]

..
   A list of acceptible vertex types and time types
   A list of edge/network types, their properties (what they store)


.. _vertex-types:

Vertex types
------------

Simple types
^^^^^^^^^^^^
The only requirement for a valid vertex type in C++ is to satisfy
:cpp:concept:`dag::network_vertex`. This means that the numeric types,
:cpp:`std::string`, :cpp:`std::pair`, :cpp:`std::tuple` and all standard library
ordered containers are accepted. On the other hand the python implementation
requires a predefined list of types at compile time, meaning that we have to
make a choice as to what vertex types would be available. At the moment certain
fundamental types are defined

.. py:class:: dag.int64

  Corresponding to :cpp:`std::int64_t` 64-bit signed integers.

.. py:class:: dag.double

  Corresponding to :cpp:`double` double precision floating-point type, almost
  always an implementation of the IEEE-754 binary64 format.

.. py:class:: dag.string

  Corresponding to :cpp:`std::string`.

.. py:class:: dag.pair[type1, type2]

  Corresponding to :cpp:`std::pair<Type1, Type2>`.

Higher-order networks
^^^^^^^^^^^^^^^^^^^^^

In addition to the vertex types listed above, the Python binding supports
one level of higher-order networks, where vertices of the network can be any of
the defined edge types as long as that edge type uses one of the above "simple"
vertex types.

Concepts
--------

Vertices
^^^^^^^^

.. cpp:concept:: template <typename T> dag::network_vertex

  Any type that is totally ordered (satisfies :cpp:`std::totally_ordered<T>`)
  and hashable with the struct :cpp:struct:`dag::hash` can be a network vertex.

.. cpp:concept:: template <typename T> dag::integer_vertex

  A :cpp:concept:`dag::network_vertex` that is also an arithmetic integer type,
  i.e., trait :cpp:`std::numeric_limits<T>::is_integer` should have a true value
  for that type.

Edges
^^^^^

.. cpp:concept:: template <typename T> dag::network_edge

  Any type can be a network edge if it is totally ordered (satisfies
  :cpp:`std::totally_ordered<T>`), hashable with both :cpp:`std::hash` and
  :cpp:struct:`dag::hash`, defines a :cpp:`VertexType` member type and certain
  function members: :cpp:`mutated_verts()`, :cpp:`mutator_verts()`,
  :cpp:`is_incident(VertexType v)`, :cpp:`is_in_incident(VertexType v)` and
  :cpp:`is_out_incident(VertexType v)`.

  The type must also provide specialisations for :cpp:func:`dag::effect_lt` and
  :cpp:func:`dag::adjacent`.

..
   network_edge, static edge and temporal edge concepts
