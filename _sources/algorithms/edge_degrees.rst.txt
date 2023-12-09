Edge degrees (orders)
=====================

Degree functions
----------------

There are multiple ways of defining the degrees for (hyper-)edges depending on
the type of edge. All edge types have the following degree functions defined:

* **Edge in-degree** referes to the number of vertices that are in-incident to
  the edge, i.e., the cardinality of the set of mutator vertices of the edge.
* **Edge out-degree** referes to the number of vertices that are out-incident
  to the edge, i.e., the cardinality of the set of mutated vertices of the edge.
* **Edge incident-degree** referes to the number of vertices incident to the
  edge. 

.. note::
   Unlike :ref:`vertex degrees <algorithms/vertex_degrees:Vertex degrees>`, edge degree
   functions do not require a network to be passed as the first argument. This
   is because the degree of an edge can be determined by the edge itself.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: edge_in_degree(edge) -> int

    .. py:function:: edge_out_degree(edge) -> int

    .. py:function:: edge_incident_degree(edge) -> int

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
        std::size_t edge_in_degree(const EdgeT& edge)

    .. cpp:function:: template <network_edge EdgeT> \
        std::size_t edge_out_degree(const EdgeT& edge)

    .. cpp:function:: template <network_edge EdgeT> \
        std::size_t edge_incident_degree(const EdgeT& edge)


For undirected edges, **degree** of a edge referes to the incident-degree of
that edge. For directed edges, the word degree on its own is vaguely-defined.
In hypergraphs, this is commonly refered to as the *order* of the edge.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: edge_degree(edge) -> int

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <undirected_network_edge EdgeT> \
        std::size_t edge_degree(const EdgeT& edge)



Edge degree sequences
---------------------

Edge degree sequence functions return the set of (in-, out- or incident-) degee of
edges in the same order as that of :py:`network.edges()`. In- and out-degree 
pair sequence is a sequence of tuples of in- and out-degrees of edges.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: edge_in_degree_sequence(network) -> List[int]

    .. py:function:: edge_out_degree_sequence(network) -> List[int]

    .. py:function:: edge_incident_degree_sequence(network) -> List[int]

    .. py:function:: edge_in_out_degree_pair_sequence(network) -> \
        List[Tuple[int, int]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
        std::vector<std::size_t> edge_in_degree_sequence(\
          const network<EdgeT>& net)

    .. cpp:function:: template <network_edge EdgeT> \
        std::vector<std::size_t> edge_out_degree_sequence(\
          const network<EdgeT>& net)

    .. cpp:function:: template <network_edge EdgeT> \
        std::vector<std::size_t> edge_incident_degree_sequence(\
          const network<EdgeT>& net)

    .. cpp:function:: template <network_edge EdgeT> \
        std::vector<std::pair<std::size_t, std::size_t>> \
          edge_in_out_degree_pair_sequence(\
            const network<EdgeT>& net)

Similar to :cpp:func:`edge_degree`, edge degree sequence without a prefix is only defined
for undirected networks.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: edge_degree_sequence(undirected_network) -> List[int]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <undirected_network_edge EdgeT> \
        std::vector<std::size_t> edge_degree_sequence(const network<EdgeT>& net)
