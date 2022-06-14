Graph operations
================

Edge induced subgraphs
----------------------

C++:

.. cpp:function:: template <network_edge EdgeT, \
       std::ranges::input_range Range> \
    requires std::same_as<std::ranges::range_value_t<Range>, EdgeT> \
    network<EdgeT> \
    edge_induced_subgraph(const network<EdgeT>& net, Range&& edges)

Python:

.. py:function:: edge_induced_subgraph(net, edges)

Returns a copy of a subset of the network :cpp:`net` consisting only of edges
:cpp:`edges` and all their incident vertices.

Vertex induced subgraphs
------------------------

C++:

.. cpp:function:: template <network_edge EdgeT, \
       std::ranges::input_range Range> \
    requires std::same_as<std::ranges::range_value_t<Range>, EdgeT::VetexType> \
    network<EdgeT> \
    vertex_induced_subgraph(const network<EdgeT>& net, Range&& verts)

Python:

.. py:function:: vertex_induced_subgraph(net, verts)

Returns a copy of a subset of the network :cpp:`net` consisting only of vertices
:cpp:`verts` and any edges with all incident vertices in :cpp:`verts`.


Adding and removings edges
--------------------------

C++:

.. cpp:function:: template <network_edge EdgeT, \
       std::ranges::input_range EdgeRange> \
    requires std::same_as<std::ranges::range_value_t<EdgeRange>, EdgeT> \
    network<EdgeT> \
    with_edges(const network<EdgeT>& net, EdgeRange&& edges)

Python:

.. py:function:: with_edges(net, edges)

Returns a copy of :cpp:`net` with edges from :cpp:`edges` along with all their
incident vertices added in.

C++:

.. cpp:function:: template <network_edge EdgeT, \
       std::ranges::input_range EdgeRange> \
    requires std::same_as<std::ranges::range_value_t<EdgeRange>, EdgeT> \
    network<EdgeT> \
    without_edges(const network<EdgeT>& net, EdgeRange&& edges)

Python:

.. py:function:: without_edges(net, edges)

Returns a copy of :cpp:`net` with edges from :cpp:`edges` removed. The returned
graph has all the vertices of the original graph.


Adding and removing vertices
----------------------------

C++:

.. cpp:function:: template <network_edge EdgeT, \
       std::ranges::input_range VertRange> \
    requires std::same_as<std::ranges::range_value_t<VertRange>,\
      EdgeT::VetexType> \
    network<EdgeT> \
    with_vertices(const network<EdgeT>& net, VertRange&& verts)

Python:

.. py:function:: with_vertices(net, verts)

Returns a copy of :cpp:`net` with vertices from :cpp:`verts` added in.


C++:

.. cpp:function:: template <network_edge EdgeT, \
       std::ranges::input_range VertRange> \
    requires std::same_as<std::ranges::range_value_t<VertRange>,\
      EdgeT::VetexType> \
    network<EdgeT> \
    without_vertices(const network<EdgeT>& net, VertRange&& verts)

Python:

.. py:function:: without_vertices(net, verts)

Returns a copy of :cpp:`net` with vertices from :cpp:`verts`, along with all
their incident edges removed.

Graph Union
-----------

C++

.. cpp:function:: template <network_edge EdgeT> \
    network<EdgeT> \
    graph_union(const network<EdgeT>& g1, const network<EdgeT>& g2)

Python:

.. py:function:: graph_union(g1, g2)


Calculates the graph union of two networks :cpp:`g1` and :cpp:`g2`: a new
network containing the union of their sets of vertices and edges.

Cartesian Product
-----------------

C++

.. cpp:function:: template <network_vertex VertT1, \
       network_vertex VertT2> \
    undirected_network<std::pair<VertT1, VertT2>> \
    cartesian_product(\
       const undirected_network<VertT1>& g1, \
       const undirected_network<VertT2>& g2)

Python:

.. py:function:: cartesian_product(\
       g1: undirected_network[vertex_type1], \
       g2: undirected_network[vertex_type2]) \
   -> undirected_network[pair[vertex_type1, vertex_type2]]

Calculates graph cartesian product of two undirected networks :cpp:`g1` and
:cpp:`g1`.

.. note:: While in C++ there are no limits on the types of vertices
   of the network (as long as they satisfy :cpp:concept:`network_vertex`)
   the Python binding only supports certain :ref:`vertex types <vertex-types>`.
   This function is not implemented for cases that would produce output vertices
   too complex to be predefined, i.e., when :py:`vertex_type1` or
   :py:`vertex_type2` are not a simple numerical or string type. In these cases
   you might want to relabel the vertices of the networks before calling this
   function.


Relabling vertices
------------------

.. warning:: Experimental API. We are still trying to find the right balance
  with these functions. The function name, parameters and available variations
  will probably change in the future versions.
