Vertex degrees
==============

Degree functions
----------------

There are multiple ways of defining the degrees for vertices depending on the
type of network at hand. All network types have the following degree types
defined:

* **In-degree** referes to the number of edges where the vertex is a member of
  their out-incident set of vertices, i.e., the cardinality of the set of edges
  that are incoming to that vertex.
* **Out-degree** referes to the number of edges where the vertex is a member of
  their in-incident set of vertices, i.e., the cardinality of the set of edges
  that are outgoing from that vertex.
* **Incident-degree** referes to the number of edges where the vertex is a
  member of their incident set of vertices, i.e., the set of edges that are
  incoming to or outgoing from that vertex. This should be the sum of in- and
  out-degree of that vertex.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: in_degree(network, vertex) -> int

    .. py:function:: out_degree(network, vertex) -> int

    .. py:function:: incident_degree(network, vertex) -> int

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
        std::size_t in_degree(const network<EdgeT>& net, \
        const typename EdgeT::VertexType& vert)

    .. cpp:function:: template <network_edge EdgeT> \
        std::size_t out_degree(const network<EdgeT>& net, \
        const typename EdgeT::VertexType& vert)

    .. cpp:function:: template <network_edge EdgeT> \
        std::size_t incident_degree(const network<EdgeT>& net, \
        const typename EdgeT::VertexType& vert)


For undirected networks, **degree** of a vertex referes to the incident-degree
of that vertex. For directed networks, the word degree on its own is
vaguely-defined.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: degree(undirected_network, vertex) -> int

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <undirected_network_edge EdgeT> \
        std::size_t degree(const network<EdgeT>& net, \
        const typename EdgeT::VertexType& vert)



Degree sequences
----------------

Degree sequence functions return the set of (in-, out- or incident-) degee of
vertices in the same order as that of :py:`network.vertices()`. In- and
out-degree pair sequence is a sequence of tuples of in- and out-degrees of
vertices.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: in_degree_sequence(network) -> List[int]

    .. py:function:: out_degree_sequence(network) -> List[int]

    .. py:function:: incident_degree_sequence(network) -> List[int]

    .. py:function:: in_out_degree_pair_sequence(network) -> \
        List[Tuple[int, int]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
        std::vector<std::size_t> in_degree_sequence(const network<EdgeT>& net)

    .. cpp:function:: template <network_edge EdgeT> \
        std::vector<std::size_t> out_degree_sequence(const network<EdgeT>& net)

    .. cpp:function:: template <network_edge EdgeT> \
        std::vector<std::size_t> incident_degree_sequence(\
          const network<EdgeT>& net)

    .. cpp:function:: template <network_edge EdgeT> \
        std::vector<std::pair<std::size_t, std::size_t>> \
        in_out_degree_pair_sequence(\
          const network<EdgeT>& net)

Similar to :cpp:func:`degree`, degree sequence without a prefix is only defined
for undirected networks.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: degree_sequence(undirected_network) -> List[int]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <undirected_network_edge EdgeT> \
        std::vector<std::size_t> degree_sequence(const network<EdgeT>& net)

