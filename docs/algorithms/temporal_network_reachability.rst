Temporal network reachability
=============================

In a temporal network, reachability is a function of time, i.e., the
possibility of going from vertex :math:`v_0` at time :math:`t_0` to :math:`v_1`
at :math:`t_1`.

Temporal reachability functions
-------------------------------

The library comes with a variety of functions that calculates the
`temporal clusters`_, the spreading cluster of an effect starting from a single
vertex at a specific time, assuming that the spreading "effect" stays in each
node for duration dictated by the `temporal adjacency`_ of that spreading
process.

The variants are similar to those of
:ref:`static network reachability <static network reachability>`, with the
possibility of starting from one vertex at one time, or calculating or
estimating spreading clusters from all vertices at all starting times.

Similar to calculating spreading starting from a single vertex at some point
time, the library allows you to run the spreading process backwards, calculating
the set of starting vertices and times that, would a spreading process start at
one of those points, can spread to our target. The contrast between this and
forward and backwards process is similar to the contrast between calculating in-
and out-components on a directed acyclic graph.

From/to a single point
^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  dag::temporal_cluster<EdgeT, AdjT> \
  dag::in_cluster(\
      const dag::network<EdgeT>& temp, \
      const AdjT& adj, \
      const typename EdgeT::VertexType& v, \
      typename EdgeT::TimeType t)

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  dag::temporal_cluster<EdgeT, AdjT> \
  dag::in_cluster(\
      const dag::network<EdgeT>& temp, \
      const AdjT& adj, \
      const EdgeT& e)


.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  dag::temporal_cluster<EdgeT, AdjT> \
  dag::out_cluster(\
      const dag::network<EdgeT>& temp, \
      const AdjT& adj, \
      const typename EdgeT::VertexType& v, \
      typename EdgeT::TimeType t)

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  dag::temporal_cluster<EdgeT, AdjT> \
  dag::out_cluster(\
      const dag::network<EdgeT>& temp, \
      const AdjT& adj, \
      const EdgeT& e)

Python:

.. py:function:: dag.in_cluster(temporal_network, \
      temporal_adjacency: adjacency_type, \
      vertex: vert_type, time: time_type) \
   -> dag.temporal_cluster[adjacency_type]

.. py:function:: dag.in_cluster(temporal_network, \
      temporal_adjacency: adjacency_type, edge: edge_type) \
   -> dag.temporal_cluster[adjacency_type]
   :noindex:


.. py:function:: dag.out_cluster(temporal_network, \
      temporal_adjacency: adjacency_type, \
      vertex: vert_type, time: time_type) \
   -> dag.temporal_cluster[adjacency_type]

.. py:function:: dag.out_cluster(temporal_network, \
      temporal_adjacency: adjacency_type, edge: edge_type) \
   -> dag.temporal_cluster[adjacency_type]
   :noindex:


From/to all points
^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  std::vector<std::pair<EdgeT, dag::temporal_cluster<EdgeT, AdjT>>> \
  dag::in_clusters(const dag::network<EdgeT>& temp, const AdjT& adj)

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  std::vector<std::pair<EdgeT, dag::temporal_cluster<EdgeT, AdjT>>> \
  dag::out_clusters(const dag::network<EdgeT>& temp, const AdjT& adj)

Python:

.. py:function:: dag.in_clusters(temporal_network, \
      temporal_adjacency: adjacency_type) \
   -> Iterable[Pair[edge_type, dag.temporal_cluster[adjacency_type]]]

.. py:function:: dag.out_clusters(temporal_network, \
      temporal_adjacency: adjacency_type) \
   -> Iterable[Pair[edge_type, dag.temporal_cluster[adjacency_type]]]

Cluster sizes from/to all points
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  std::vector<std::pair<EdgeT, dag::temporal_cluster_size<EdgeT, AdjT>>> \
  dag::in_cluster_sizes(const dag::network<EdgeT>& temp, const AdjT& adj)

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  std::vector<std::pair<EdgeT, dag::temporal_cluster_size<EdgeT, AdjT>>> \
  dag::out_cluster_sizes(const dag::network<EdgeT>& temp, const AdjT& adj)

Python:

.. py:function:: dag.in_cluster_sizes(temporal_network, \
      temporal_adjacency: adjacency_type) \
   -> Iterable[Pair[edge_type, dag.temporal_cluster_size[adjacency_type]]]

.. py:function:: dag.out_cluster_sizes(temporal_network, \
      temporal_adjacency: adjacency_type) \
   -> Iterable[Pair[edge_type, dag.temporal_cluster_size[adjacency_type]]]


Cluster size estimates from/to all points
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  std::vector<std::pair<EdgeT,\
   dag::temporal_cluster_size<EdgeT, AdjT>>> \
  dag::in_cluster_size_estimates(\
   const dag::network<EdgeT>& temp, const AdjT& adj, \
   typename EdgeT::TimeType time_resolution, \
   std::size_t seed)

.. cpp:function:: template <dag::temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> \
  std::vector<std::pair<EdgeT,\
   dag::temporal_cluster_size_estimate<EdgeT, AdjT>>> \
  dag::out_cluster_size_estimates(\
   const dag::network<EdgeT>& temp, const AdjT& adj, \
   typename EdgeT::TimeType time_resolution, \
   std::size_t seed)

Python:

.. py:function:: dag.in_cluster_size_estimates(temporal_network, \
      temporal_adjacency: adjacency_type, \
      time_resolution: time_type, seed: int) \
   -> Iterable[Pair[edge_type, \
         dag.temporal_cluster_size_estimate[adjacency_type]]]

.. py:function:: dag.out_cluster_size_estimates(temporal_network, \
      temporal_adjacency: adjacency_type, \
      time_resolution: time_type, seed: int) \
   -> Iterable[Pair[edge_type, \
         dag.temporal_cluster_size_estimate[adjacency_type]]]


Temporal adjacency
------------------

For the case of :ref:`static network reachability <static network reachability>`
we had a nice and concrete definition of adjacency. For example, in an
undirected network if two edges share at least one incident vertex, an "effect"
(e.g., a disease or a gossip) transmitted through one edge can also be
transmitted through the other edge.

For temporal networks, however, this gets slightly more complicated. For
starters, for an effect transmitted through event :math:`e_1` to be transmitted
again by another event :math:`e_2`, the two event have to happen in the correct
order.

Many categories of effects have further temporal restrictions on adjacency of
two events, e.g., many spreading processes have a maximum waiting-time which
puts an upper-bound on the time distance between two events. For example, many
diseases have a maximum duration where a patient can remain infectious.

This library defines a few common types of temporal adjacency. The `simple
adjacency`_ describes the case where the only restriction is due to limitation
of cause and effect, with no further limitations. Other temporal adjacency types
describe commonly used stochastic or deterministic limits on spreading.

Simple adjacency
^^^^^^^^^^^^^^^^

C++:

.. cpp:class:: template <temporal_edge EdgeT> dag::temporal_adjacency::simple

  .. cpp:function:: simple()

Python:

.. py:class:: dag.temporal_adjacency.simple[edge_type]()

The simple temporal adjacency specifies the physical minimum requirements for
two events to be considered adjacent. The 

.. note:: Two event happening at the same time cannot be adjacent. If your
   network representation has low temporal resolutoin, you might need to
   manually adjust timestamps.

Limited waiting-time adjacency
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:class:: template <temporal_edge EdgeT> \
   dag::temporal_adjacency::limited_waiting_time

  .. cpp:function:: limited_waiting_time(typename EdgeType::TimeType dt)

Python:

.. py:class:: dag.temporal_adjacency.limited_waiting_time[edge_type](\
      dt: time_type)


Exponential adjacency
^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:class:: template <temporal_edge EdgeT> \
   dag::temporal_adjacency::exponential

  .. cpp:function:: exponential(\
      typename EdgeType::TimeType rate, \
      std::size_t seed)

Python:

.. py:class:: dag.temporal_adjacency.exponential[edge_type](\
      rate: time_type, seed: int)

In an exponential temporal adjacency regime, the effect remains on an affected
vertex for a duration of time drawn from an exponential distribution with the
given rate :cpp:`rate`. The parameter :cpp:`seed` makes sure that the same
instance of a stochastic adjacency type on the same network produces the same
outcome every time.

.. note:: The exponential temporal adjacency type, similar to the exponential
   distribution, is only well defined for continious time types. If you are
   dealing with data with timestamps that cannot be represented faithfully as
   continious variables, you might want to use a `geometric adjacency`_ type.

Geometric adjacency
^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:class:: template <temporal_edge EdgeT> \
   dag::temporal_adjacency::geometric

  .. cpp:function:: geometric(\
      typename EdgeType::TimeType rate, \
      std::size_t seed) const

Python:

.. py:class:: dag.temporal_adjacency.exponential[edge_type](\
      rate: time_type, seed: int)

In an geometric temporal adjacency regime, the effect remains on an affected
vertex for a duration of time drawn from a geometric distribution with the
given rate :cpp:`rate` and mean :math:`rate^{-1}`. The parameter :cpp:`seed`
makes sure that the same instance of a stochastic adjacency type on the same
network produces the same outcome every time.

.. note:: The geometric temporal adjacency type, similar to the geometric
   distribution, is only well defined for discrete time types. If you are
   dealing with data with timestamps that cannot be represented faithfully as
   discrete variables, you might want to use an `exponential adjacency`_ type.


Your own temporal adjacency type
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:concept:: template <typename T> dag::temporal_adjacency

In C++, you can use your own temporal adjacency type as long as it satisfies the
concept :cpp:concept:`dag::temporal_adjacency`. To wit, that it should have well
defined member types :cpp:`EdgeType` and :cpp:`VetexType` and defines member
functions :cpp:`linger(EdgeType e, VetexType v)` and
:cpp:`maximum_linger(VertexType v)`, the former describing how long vertex
:cpp:`v` remains affected by an effect transmitted by event :cpp:`e`, and the
latter describing a worst case (upper-bound) on the duration that a vertex
:cpp:`v` can remain affected by an effect.

Temporal clusters
-----------------

Clusters are to temporal networks what a component is to a static network. They
store subsets of the temporal network. While storing a subset of a static
network required only storing a set of vertices, a subset of a temporal network
also requires temporal information.

.. cpp:class:: template <temporal_edge EdgeT, \
   temporal_adjacency::temporal_adjacency AdjT> temporal_cluster

   .. cpp:type:: VertexType

   .. cpp:type:: AdjacencyType

   .. cpp:type:: IteratorType

   .. cpp:function:: template <std::ranges::input_range Range> \
        requires std::convertible_to<std::ranges::range_value_t<Range>, EdgeT> \
        void insert(const Range& events)

   .. cpp:function:: void insert(const EdgeT& e)

   .. cpp:function:: void merge(const temporal_cluster<EdgeT, AdjT>& other)

   .. cpp:function:: bool operator==(\
         const temporal_cluster<EdgeT, AdjT>& c) const

   .. cpp:function:: std::size_t size() const

   .. cpp:function:: bool contains(const EdgeT& e) const

   .. cpp:function:: bool covers(typename EdgeT::VertexType v, typename \
         EdgeT::TimeType t) const

   .. cpp:function:: bool empty() const

   .. cpp:function:: IteratorType begin() const

   .. cpp:function:: IteratorType end() const

   .. cpp:function:: const std::unordered_map<typename EdgeT::VertexType, \
            dag::interval_set<typename EdgeT::TimeType>, \
         dag::hash<typename EdgeT::VertexType>>& \
         interval_sets() const

   .. cpp:function:: std::pair<\
            typename EdgeT::TimeType, typename EdgeT::TimeType>\
         lifetime() const;

   .. cpp:function:: std::size_t volume() const

   .. cpp:function:: typename EdgeT::TimeType mass() const


.. cpp:class:: template <temporal_edge EdgeT, \
         temporal_adjacency::temporal_adjacency AdjT> temporal_cluster_size

   .. cpp:type:: VertexType

   .. cpp:type:: AdjacencyType

   .. cpp:function:: explicit temporal_cluster_size(\
         const temporal_cluster<EdgeT, AdjT>& c)

   .. cpp:function:: std::size_t size() const

   .. cpp:function:: std::pair<\
            typename EdgeT::TimeType, typename EdgeT::TimeType> \
          lifetime() const

   .. cpp:function:: std::size_t volume() const

   .. cpp:function:: typename EdgeT::TimeType mass() const


.. cpp:class:: template <temporal_edge EdgeT, \
         temporal_adjacency::temporal_adjacency AdjT>\
      temporal_cluster_size_estimate

   .. cpp:type:: VertexType

   .. cpp:type:: AdjacencyType

   .. cpp:function:: double size_estimate() const

   .. cpp:function:: std::pair<\
            typename EdgeT::TimeType, typename EdgeT::TimeType> \
          lifetime() const

   .. cpp:function:: double volume_estimate() const

   .. cpp:function:: double mass_estimate() const

   .. cpp:function:: EdgeT::TimeType temporal_resolution() const
