Networks and network types
==========================

Reticula support static and temporal networks involving two (dyadic) or more
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
:cpp:`undirected_network<std::int64_t>` indicates an undirected static
network with 64-bit signed integer vertices. The Python API, which by necessity
has to carry the same information, simulates this in a form similar to the
existing `type annotation`_ syntax: :py:`undirected_network[int64]`.
Temporal networks also need to know about the time type that they should store.
For example :py:`undirected_temporal_network[int64, double]`
marks a continuous time undirected temporal network with integer vertices.

If the type syntax looks verbose, remember that you can, and probably should,
assign a human-readable name to repeatedly-used types in your code. This way you
can avoid repeating yourself without compromising on type safety:

.. code-block:: python

      import reticula as ret

      network_type = ret.undirected_network[ret.int64]
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

      import reticula as ret

      g1 = ret.undirected_network[ret.int64]() # an empty network
      g2 = ret.undirected_network[ret.int64](edges=[(1, 2), (2, 3)])
      g3 = ret.undirected_network[ret.int64](
               edges=[(1, 2), (2, 3)], verts=[1, 2, 3, 4, 5, 6])


This mimics the C++ brace initialisation syntax:

.. code-block:: cpp

      undirected_network<std::int64_t> g1; // an empty network
      undirected_network<std::int64_t> g2({{1, 2}, {2, 3}});
      undirected_network<std::int64_t> g3(
         {{1, 2}, {2, 3}},
         {1, 2, 3, 4, 5, 6});


The list of vertices is not required, but providing it can inform the network
that a vertex of with that name exists, even if there are not edges connected
to it.

.. note::
   The Python binding implicit conversion from tuples to edge types is currently
   sensetive to mixing different numeric types, e.g., if it is expecting a
   2-tuple of double and you pass a 2-tuple of integers, it cannot perform an
   implicit conversion. It is however okay to use a list instead of a tuple and
   vice versa.


Edges and vertices
^^^^^^^^^^^^^^^^^^

Edges and vertices are accessible through member functions of the same name.

.. code-block:: python

      g3.edges() # list of two edges
      g3.vertices() # list six vertices

You can also get the network edges sorted by :cpp:`operator<`
(:py:`operator.__lt__` in Python) or :cpp:func:`effect_lt`
(:py:func:`effect_lt`) through functions :py:`edges_cause` and
:py:`edges_effect` member functions. In a temporal network the result of the
former will be sorted by cause time and the latter by effect time of the events.
In static networks they return the same output.

Incident edges
^^^^^^^^^^^^^^

Edges incident to a vertex can be accessed using the :py:`incident_edges`
methods. For directed network types, methods :py:`out_edges` and :py:`in_edges`
distinguish between inward and outward edges, while :py:`indicent_edges` does
not.

.. code-block:: python

      g3.incident_edges(3) # => [undirected_edge[int64](2, 3)]
      g3.out_edges(3) # => same as above, as the network is undirected
      g3.in_edges(3) # => same as above, as the network is undirected



Successors, predecessors and neighbours
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The set of neighbours of a vertex in the network can be achieved using the
method :py:`neighbours`. Methods :py:`successors` and :py:`predecessors` provide
directed network equivalents.


.. code-block:: python

      g3.neighbours(2) # => [3, 1]
      g3.successors(2) # => same as above, as the network is undirected
      g3.predecessors(2) # => same as above, as the network is undirected

Vertex degree
^^^^^^^^^^^^^

The degree of each vertex can be calculated using the method :py:`degree`,
:py:`in_degree` and :py:`out_degree`. For hypergraphs and hypergraph temporal
networks, the degree refers to the number of unique edges, as opposed to the
number of neighbours.

.. code-block:: python

      g3.degree(2) # => 2
      g3.out_degree(2) # => same as above, as the network is undirected
      g3.in_degree(2) # => same as above, as the network is undirected

Network types
-------------

.. cpp:class:: template <network_edge EdgeT> network<EdgeT>


Undirected static networks
^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT> \
   undirected_network<VertT>

.. py:class:: undirected_network[vertex_type]


Directed static networks
^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT> \
   directed_network<VertT>

.. py:class:: directed_network[vertex_type]


Undirected static hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT> \
   undirected_hypernetwork<VertT>

.. py:class:: undirected_hypernetwork[vertex_type]


Directed static hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT> \
   directed_hypernetwork<VertT>

.. py:class:: directed_hypernetwork[vertex_type]


Directed temporal networks
^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT, typename TimeT> \
   undirected_temporal_network<VertT, TimeT>

.. py:class:: undirected_temporal_network[vertex_type, time_type]

Directed temporal networks
^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT, typename TimeT> \
   directed_temporal_network<VertT, TimeT>

.. py:class:: directed_temporal_network[vertex_type, time_type]


Directed delayed temporal networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT, typename TimeT> \
   directed_delayed_temporal_network<VertT, TimeT>

.. py:class:: directed_delayed_temporal_network[vertex_type, time_type]


Undirected temporal hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT, typename TimeT> \
   undirected_temporal_hypernetwork<VertT, TimeT>

.. py:class:: undirected_temporal_hypernetwork[vertex_type, time_type]

Directed temporal hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT, typename TimeT> \
   directed_temporal_hypernetwork<VertT, TimeT>

.. py:class:: directed_temporal_hypernetwork[vertex_type, time_type]

Directed delayed temporal hyper-networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. cpp:class:: template <network_vertex VertT, typename TimeT> \
   directed_delayed_temporal_hypernetwork<VertT, TimeT>

.. py:class:: directed_delayed_temporal_hypernetwork[\
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
:cpp:concept:`network_vertex`. This means that the numeric types,
:cpp:`std::string`, :cpp:`std::pair`, :cpp:`std::tuple` and all standard library
ordered containers are accepted. On the other hand the python implementation
requires a predefined list of types at compile time, meaning that we have to
make a choice as to what vertex types would be available. At the moment certain
fundamental types are defined

.. py:class:: int64

  Corresponding to :cpp:`std::int64_t` 64-bit signed integers.

.. py:class:: string

  Corresponding to :cpp:`std::string`.

.. py:class:: pair[type1, type2]

  Corresponding to :cpp:`std::pair<Type1, Type2>`.

Higher-order networks
^^^^^^^^^^^^^^^^^^^^^

In addition to the vertex types listed above, the Python binding supports
one level of higher-order network, where vertices of the network can be any of
the defined edge types as long as that edge type uses one of the above "simple"
vertex types. The C++ library supports any level of higher-order networks.

Time Types
----------
In C++ it is possible to use any arithmetic type for timestamps. In the Python
binding, in addition to the previously mentioned :py:class:`int64` integer type
you can use one of the following pre-defined types:


.. py:class:: double

  Corresponding to :cpp:`double` double precision floating-point type, almost
  always an implementation of the IEEE-754 binary64 format.

Concepts
--------

Vertices
^^^^^^^^

.. cpp:concept:: template <typename T> network_vertex

  Any type that is totally ordered (satisfies :cpp:`std::totally_ordered<T>`)
  and hashable with the struct :cpp:struct:`hash` can be a network vertex.

.. cpp:concept:: template <typename T> integer_vertex

  A :cpp:concept:`network_vertex` that is also an arithmetic integer type,
  i.e., trait :cpp:`std::numeric_limits<T>::is_integer` should have a true value
  for that type.

Edges
^^^^^

.. cpp:concept:: template <typename T> network_edge

  Any type can be a network edge if it is totally ordered (satisfies
  :cpp:`std::totally_ordered<T>`), hashable with both :cpp:`std::hash` and
  :cpp:struct:`hash`, defines a :cpp:`VertexType` member type and certain
  function members: :cpp:`mutated_verts()`, :cpp:`mutator_verts()`,
  :cpp:`is_incident(VertexType v)`, :cpp:`is_in_incident(VertexType v)` and
  :cpp:`is_out_incident(VertexType v)`.

  The type must also provide specialisations for :cpp:func:`effect_lt` and
  :cpp:func:`adjacent`.

.. cpp:concept:: template <typename T> temporal_edge

  A :cpp:concept:`network_edge` that carries time information, by defining
  member types :cpp:`TimeType` which should be an arithmatic type and
  :cpp:`StaticProjectionType` which should be a :cpp:concept:`static_edge` and
  member functions :cpp:`cause_time()`, :cpp:`effect_time()` and
  :cpp:`static_projection()`.

.. cpp:concept:: template <typename T> static_edge

  A :cpp:concept:`network_edge` that does not carry time information by not
  defining member function :cpp:`effect_time()`.


Degree/weight ranges
^^^^^^^^^^^^^^^^^^^^

.. cpp:concept:: template <typename T> degree_range

  A range (i.e., satisfies :cpp:`std::ranges::range`) with integer values.

.. cpp:concept:: template <typename T> degree_pair_range

  A range (i.e., satisfies :cpp:`std::ranges::range`) with pairs of integers as
  values, representing in- and out-degree of each vertex.

.. cpp:concept:: template <typename T> weight_range

  A range (i.e., satisfies :cpp:`std::ranges::range`) with arithmetic values.

.. cpp:concept:: template <typename T> weight_pair_range

  A range (i.e., satisfies :cpp:`std::ranges::range`) with pairs of arithmetic
  values, Corresponding to in- and out-degree weigts for each vertex.
