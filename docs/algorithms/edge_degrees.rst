Edge degrees (orders)
=====================

Degree functions
----------------

There are multiple ways of defining the degrees (orders) for (hyper-)edges
depending on the type of edge. All edge types have the following degree
functions defined:

* **Edge in-degree** referes to the number of vertices that are in-incident to
  the edge, i.e., the cardinality of the set of mutator vertices of the edge.
* **Edge out-degree** referes to the number of vertices that are out-incident
  to the edge, i.e., the cardinality of the set of mutated vertices of the edge.
* **Edge incident-degree** referes to the number of vertices incident to the
  edge. 

.. note::
   Unlike :ref:`vertex degrees <algorithms/vertex_degrees:Vertex degrees>`, edge degree
   functions do not require a network to be passed as the first argument. This
   is because the degree of an edge can be determined from the edge itself.

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


.. code-block:: pycon

  >>> import reticula as ret
  >>> edge = ret.undirected_edge[ret.int64](0, 1)
  >>> ret.edge_in_degree(edge)
  2
  >>> ret.edge_out_degree(edge)
  2
  >>> ret.edge_incident_degree(edge)
  2
  >>> hyperedge = ret.directed_hyperedge[ret.int64]([0, 1, 2], [2, 3])
  >>> ret.edge_in_degree(hyperedge)
  3
  >>> ret.edge_out_degree(hyperedge)
  2
  >>> ret.edge_incident_degree(hyperedge)
  4


For undirected edges, **degree** of a (hyper)edge referes to the
incident-degree of that edge. For directed edges, the word degree on its own is
vaguely-defined. In hypergraphs, this is commonly refered to as the *order* of
the edge.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: edge_degree(edge) -> int

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <undirected_network_edge EdgeT> \
        std::size_t edge_degree(const EdgeT& edge)

.. code-block::

  >>> import reticula as ret
  >>> edge = ret.undirected_edge[ret.int64](0, 1)
  >>> ret.edge_degree(edge)
  2
  >>> edge = ret.undirected_hyperedge[ret.int64]([0, 1, 2, 3])
  >>> ret.edge_degree(edge)
  4

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

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> g = ret.random_directed_expected_degree_sequence_hypergraph[ret.int64](
  ...            vertex_in_out_weight_sequence=[(2, 2), (2, 2), (1, 1), (1, 1)],
  ...            edge_in_out_weight_sequence=[(2, 2), (2, 2), (1, 1), (1, 1)],
  ...            random_state=gen)
  >>> ret.edge_in_degree_sequence(g)
  [0, 3, 4, 2]
  >>> ret.edge_out_degree_sequence(g)
  [2, 3, 2, 0]
  >>> ret.edge_incident_degree_sequence(g)
  [2, 4, 4, 2]
  >>> ret.edge_in_out_degree_pair_sequence(g)
  [(0, 2), (3, 3), (4, 2), (2, 0)]


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

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> g = ret.random_expected_degree_sequence_hypergraph[ret.int64](
  ...            vertex_weight_sequence=[2, 2, 1, 1],
  ...            edge_weight_sequence=[2, 2, 1, 1],
  ...            random_state=gen)
  >>> g.edges()
  [undirected_hyperedge[int64]([]), undirected_hyperedge[int64]([0, 1]), undirected_hyperedge[int64]([0, 1, 3])]
  >>> ret.edge_degree_sequence(g)
  [0, 2, 3]
