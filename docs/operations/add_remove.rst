Add/Remove operations
=====================

Networks in Reticula are immutable. This means that operations that add or
remove vertices or edges from a network do not modify the original nework but
return a new network. The advantage of immutability is that it makes it easier
to reason about the code and to avoid bugs that arise from side-effects.

On the other hand, immutability makes certain operations, such as those
presented here, less efficient. As currently implemented in Reticula, an
add/remove operation essentially triggers a copy of the entire original network
object. In practice, the performance difference is not usually a problem, as
copyting even quite large networks objects are quiet fast, but it is something
to keep in mind.

When performing add/remove operations on very large networks, please also keep
in mind the simultanious existence of both "copies" when calculating the peak
memory usage of the code using these operations.

As a rule of thumb, if you need to perform a sequence of add/remove operations
on a network, it is better to do as many operations as possible in fewer batches,
e.g. instead of adding one edge at a time, add all edges at once.

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


.. code-block:: pycon

  >>> import reticula as ret
  >>> net = ret.cycle_graph[ret.int64](size=8)
  >>> net
  <undirected_network[int64] with 8 verts and 8 edges>
  >>> edges = [(0, 5), (1, 6), (2, 4)]
  >>> net = ret.with_edges(net, edges)
  >>> net
  <undirected_network[int64] with 8 verts and 11 edges>

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

.. code-block:: pycon

   >>> import reticula as ret
   >>> net = ret.cycle_graph[ret.int64](size=8)
   >>> net
   <undirected_network[int64] with 8 verts and 8 edges>
   >>> edges = [(0, 1), (2, 3)]
   >>> net = ret.without_edges(net, edges)
   >>> net
   <undirected_network[int64] with 8 verts and 6 edges>


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


.. code-block:: pycon

  >>> import reticula as ret
  >>> net = ret.cycle_graph[ret.int64](size=8)
  >>> net
  <undirected_network[int64] with 8 verts and 8 edges>
  >>> verts = [8, 9, 10]
  >>> net = ret.with_vertices(net, verts)
  >>> net
  <undirected_network[int64] with 11 verts and 8 edges>


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

.. code-block:: pycon

   >>> import reticula as ret
   >>> net = ret.cycle_graph[ret.int64](size=8)
   >>> net
   <undirected_network[int64] with 8 verts and 8 edges>
   >>> verts = [0, 1, 2]
   >>> net = ret.without_vertices(net, verts)
   >>> net
   <undirected_network[int64] with 5 verts and 4 edges>
