Add/Remove operations
=====================

Adding and removings edges
--------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: with_edges(network, edges)


  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range EdgeRange> \
        requires std::same_as<std::ranges::range_value_t<EdgeRange>, EdgeT> \
        network<EdgeT> \
        with_edges(const network<EdgeT>& net, EdgeRange&& edges)

Returns a copy of :cpp:`net` with edges from :cpp:`edges` along with all their
incident vertices added in.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: without_edges(network, edges)


  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range EdgeRange> \
        requires std::same_as<std::ranges::range_value_t<EdgeRange>, EdgeT> \
        network<EdgeT> \
        without_edges(const network<EdgeT>& net, EdgeRange&& edges)

Returns a copy of :cpp:`net` with edges from :cpp:`edges` removed. The returned
graph has all the vertices of the original graph.


Adding and removing vertices
----------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: with_vertices(network, verts)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range VertRange> \
        requires std::same_as<std::ranges::range_value_t<VertRange>,\
          EdgeT::VetexType> \
        network<EdgeT> \
        with_vertices(const network<EdgeT>& net, VertRange&& verts)

Returns a copy of :cpp:`net` with vertices from :cpp:`verts` added in.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: without_vertices(network, verts)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range VertRange> \
        requires std::same_as<std::ranges::range_value_t<VertRange>,\
          EdgeT::VetexType> \
        network<EdgeT> \
        without_vertices(const network<EdgeT>& net, VertRange&& verts)

Returns a copy of :cpp:`net` with vertices from :cpp:`verts`, along with all
their incident edges removed.
