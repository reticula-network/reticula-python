.. _static network reachability:

Static network reachability
===========================

The algorithms described in this page deal with the topic of reachability in
different network types. **Reachability** is the ability to get from one vertex
to another, but only through edges of the network. If the network is directed,
the *path* between two vertices should always be following the directions of the
edges.

The functions presented here accept both static dyadic and hypernetworks.

Component types
---------------

.. cpp:class:: template <network_vertex VertT> component

.. py:class:: component[vert_type]

A *component* is a set of network vertices. Components are iterable both in C++,
through satisfying the :cpp:`std::ranges::forward_range` and
:cpp:`std::ranges::sized_range` concepts, and in Python by implementing
:py:`__iter__`.


.. cpp:class:: template <network_vertex VertT> component_size

.. py:class:: component_size[vert_type]



.. cpp:class:: template <network_vertex VertT> component_estimate

.. py:class:: component_size_estimate[vert_type]

Weak-connectivity
-----------------

C++:

.. cpp:function:: template <static_directed_edge EdgeT> \
  component<typename EdgeT::VertexType> \
  weakly_connected_component(\
    const network<EdgeT>& dir, \
    const typename EdgeT::VertexType& vert, \
    std::size_t size_hint = 0)

Python:

.. py:function:: weakly_connected_component(directed_network, \
  vert: vert_type, size_hint: int = 0) -> component[vert_type]

Finds the weakly-connected component for vertex :cpp:`vert`. The parameter
:cpp:`size_hint` can help reduce memory re-allocations if you already have a
rough estimate (or even better: a good upper-bound) on the weakly-connected
component size you expect to get. If not, you can rely on the default behaviour.


C++:

.. cpp:function:: template <static_directed_edge EdgeT> \
  std::vector<component<typename EdgeT::VertexType>> \
  weakly_connected_components(\
    const network<EdgeT>& dir, \
    bool singletons = true)

Python:

.. py:function:: weakly_connected_components(directed_network, \
  singletons: bool = True) -> Iterable[component[vert_type]]

Returns all weakly-connected components of the parameter network. Implementation
is based on consecutive unions on a disjoint-set data structure of vertices
:cite:p:`galler1964improved,galil1991data`.

If you are not interested in weakly-connected components with only a single
vertex, set the :cpp:`singletons` to :cpp:`false`.


C++:

.. cpp:function:: template <static_directed_edge EdgeT> \
  bool is_weakly_connected(const network<EdgeT>& dir)

Python:

.. py:function:: is_weakly_connected(directed_network) -> bool

Returns true if the network is weakly-connected: if all pairs of vertices
can be connected through the network edges, if we forget about the directions of
those edges, i.e., there exists an undirected path between every pair of
vertices.

In- and out-components
----------------------


From a single source
^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <static_directed_edge EdgeT> \
  component<typename EdgeT::VertexType> \
  in_component(\
      const network<EdgeT>& dir, \
      const typename EdgeT::VertexType& root, \
      std::size_t size_hint = 0)

.. cpp:function:: template <static_directed_edge EdgeT> \
  component<typename EdgeT::VertexType> \
  out_component(\
      const network<EdgeT>& dir, \
      const typename EdgeT::VertexType& root, \
      std::size_t size_hint = 0)

Python:

.. py:function:: in_component(directed_network, vert: vert_type,\
  size_hint: int = 0) -> component[vert_type]

.. py:function:: out_component(directed_network, vert: vert_type,\
  size_hint: int = 0) -> component[vert_type]


Calculate the in- or out-component of a vertex in a static directed network.

From all vertices
^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <static_directed_edge EdgeT> \
  std::vector<std::pair<\
    typename EdgeT::VertexType, \
    component<typename EdgeT::VertexType>>> \
  in_components(const network<EdgeT>& dir)

.. cpp:function:: template <static_directed_edge EdgeT> \
  std::vector<std::pair<\
    typename EdgeT::VertexType, \
    component<typename EdgeT::VertexType>>> \
  out_components(const network<EdgeT>& dir)

Python:

.. py:function:: in_components(directed_network) \
  -> iterable[pair[vert_type, component[vert_type]]]

.. py:function:: out_components(directed_network) \
  -> iterable[pair[vert_type, component[vert_type]]]

Calculates the in- or out-components of all vertices in a static directed
network.

In- and out-component sizes
^^^^^^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <static_directed_edge EdgeT> \
  std::vector<std::pair<\
    typename EdgeT::VertexType, \
    component_size<typename EdgeT::VertexType>>> \
  in_component_sizes(const network<EdgeT>& dir)

.. cpp:function:: template <static_directed_edge EdgeT> \
  std::vector<std::pair<\
    typename EdgeT::VertexType, \
    component_size<typename EdgeT::VertexType>>> \
  out_component_sizes(const network<EdgeT>& dir)

Python:

.. py:function:: in_component_sizes(directed_network) \
  -> iterable[pair[vert_type, component_size[vert_type]]]

.. py:function:: out_component_sizes(directed_network) \
  -> iterable[pair[vert_type, component_size[vert_type]]]

Calculates the in- or out-component *sizes* of all vertices in a static
directed network. Compared to calculating all in- or out-components, this uses
less memory in some cases.

In- and out-component size estimates
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <static_directed_edge EdgeT> \
  std::vector<std::pair<\
    typename EdgeT::VertexType, \
    component_size_estimate<typename EdgeT::VertexType>>> \
  in_component_size_estimates(\
    const network<EdgeT>& dir, std::size_t seed = 0)

.. cpp:function:: template <static_directed_edge EdgeT> \
  std::vector<std::pair<\
    typename EdgeT::VertexType, \
    component_size_estimate<typename EdgeT::VertexType>>> \
  out_component_size_estimates(\
    const network<EdgeT>& dir, std::size_t seed = 0)

Python:

.. py:function:: in_component_size_estimates(directed_network) \
  -> iterable[pair[vert_type, component_size_estimate[vert_type]]]

.. py:function:: out_component_size_estimates(directed_network) \
  -> iterable[pair[vert_type, component_size_estimate[vert_type]]]

*Estimates* the in- or out-component sizes of all vertices in a static directed
network. Compared to calculating all in- or out-components and in- and
out-component sizes, this uses much less memory and is much faster to run in
many cases.

Undirected static networks
--------------------------


Connected component of a specific vertex
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <static_undirected_edge EdgeT> \
  component<typename EdgeT::VertexType> \
  connected_component(\
      const network<EdgeT>& net, \
      const typename EdgeT::VertexType& vert, \
      std::size_t size_hint = 0)

Python:

.. py:function:: connected_component(\
  undirected_network, vert: vert_type, size_hint : int = 0) -> \
  component[vert_type]

Returns the connected component that vertex :cpp:`vert` belongs to. A connected
component is a maximal subset of vertices of the network where all vertices can
reach all others.


All connected components
^^^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <static_undirected_edge EdgeT> \
  std::vector<component<typename EdgeT::VertexType>> \
  connected_components(\
      const network<EdgeT>& net, \
      bool singletons = true)

Python:

.. py:function:: connected_components(undirected_network, \
  singletons: bool = True) -> Iterable[components[vert_type]]

Returns all connected components of the static undirected network.

All connected components
^^^^^^^^^^^^^^^^^^^^^^^^

C++:

.. cpp:function:: template <static_undirected_edge EdgeT> \
  bool is_connected(const network<EdgeT>& net);

Python:

.. py:function:: is_connected(undirected_network) -> bool

Returns :cpp:`true` if all vertices of the network are reachable from all other.

Source-destination reachability
-------------------------------

C++:

.. cpp:function:: template <static_edge EdgeT> \
  bool is_reachable(\
      const network<EdgeT>& net, \
      const typename EdgeT::VertexType& source, \
      const typename EdgeT::VertexType& destination)

Python:

.. py:function:: is_reachable(directed_network, source, destination) -> bool

Returns :cpp:`true` if the vertex :cpp:`destination` is reachable from the
vertex :cpp:`source` by following edges in the legal direction. This function
accepts all static network types.
