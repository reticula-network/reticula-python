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
