Subgraph operations
===================

Edge induced subgraphs
----------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: edge_induced_subgraph(net, edges)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range Range> \
        requires std::same_as<std::ranges::range_value_t<Range>, EdgeT> \
        network<EdgeT> \
        edge_induced_subgraph(const network<EdgeT>& net, Range&& edges)

Returns a copy of a subset of the network :cpp:`net` consisting only of edges
:cpp:`edges` and all their incident vertices.

.. code-block:: pycon

  >>> import reticula as ret
  >>> net = ret.cycle_graph[ret.int64](size=8)
  >>> edges = [(0, 1), (1, 2), (2, 3)]
  >>> subgraph = ret.edge_induced_subgraph(net, edges)
  >>> subgraph
  <undirected_network[int64] with 4 verts and 3 edges>
  >>> subgraph.edges()
  [undirected_edge[int64](0, 1), undirected_edge[int64](1, 2), undirected_edge[int64](2, 3)]
  >>> subgraph.vertices()
  [0, 1, 2, 3]


Vertex induced subgraphs
------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: vertex_induced_subgraph(net, verts)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range Range> \
        requires std::same_as<std::ranges::range_value_t<Range>, EdgeT::VetexType> \
        network<EdgeT> \
        vertex_induced_subgraph(const network<EdgeT>& net, Range&& verts)

Returns a copy of a subset of the network :cpp:`net` consisting only of vertices
:cpp:`verts` and any edges with all incident vertices in :cpp:`verts`.

.. code-block:: pycon

   >>> import reticula as ret
   >>> net = ret.cycle_graph[ret.int64](size=8)
   >>> verts = [0, 1, 2, 5]
   >>> subgraph = ret.vertex_induced_subgraph(net, verts)
   >>> subgraph
   <undirected_network[int64] with 3 verts and 2 edges>
   >>> subgraph.edges()
   [undirected_edge[int64](0, 1), undirected_edge[int64](1, 2)]
   >>> subgraph.vertices()
   [0, 1, 2, 5]
