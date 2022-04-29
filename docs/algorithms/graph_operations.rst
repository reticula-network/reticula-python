Graph operations
================

Edge induced subgraphs
----------------------

C++:

.. cpp:function:: template <dag::network_edge EdgeT, \
       std::ranges::input_range Range> \
    requires std::same_as<std::ranges::range_value_t<Range>, EdgeT> \
    dag::network<EdgeT> \
    edge_induced_subgraph(const dag::network<EdgeT>& net, const Range& edges)

Python:

.. py:function:: dag.edge_induced_subgraph(net, edges)

Returns a copy of a subset of the network :cpp:`net` consisting only of edges
:cpp:`edges` and all their incident vertices.

Vertex induced subgraphs
------------------------

C++:

.. cpp:function:: template <dag::network_edge EdgeT, \
       std::ranges::input_range Range> \
    requires std::same_as<std::ranges::range_value_t<Range>, EdgeT::VetexType> \
    dag::network<EdgeT> \
    vertex_induced_subgraph(const dag::network<EdgeT>& net, const Range& verts)

Python:

.. py:function:: dag.vertex_induced_subgraph(net, verts)

Returns a copy of a subset of the network :cpp:`net` consisting only of vertices
:cpp:`verts` and any edges with all incident vertices in :cpp:`verts`.


Adding edges
------------

C++

.. cpp:function:: template <dag::network_edge EdgeT, \
       std::ranges::input_range EdgeRange> \
    requires std::same_as<std::ranges::range_value_t<EdgeRange>, EdgeT> \
    dag::network<EdgeT> \
    with_edges(const dag::network<EdgeT>& net, const EdgeRange& edges)

Python:

.. py:function:: dag.with_edges(net, edges)

Returns a copy of :cpp:`net` with edges from :cpp:`edges` along with all their
incident vertices added in.

Adding vertices
---------------

C++

.. cpp:function:: template <dag::network_edge EdgeT, \
       std::ranges::input_range VertRange> \
    requires std::same_as<std::ranges::range_value_t<VertRange>,\
      EdgeT::VetexType> \
    dag::network<EdgeT> \
    with_vertices(const dag::network<EdgeT>& net, const VertRange& verts)

Python:

.. py:function:: dag.with_vertices(net, verts)

Returns a copy of :cpp:`net` with vertices from :cpp:`verts` added in.

Graph Union
-----------

C++

.. cpp:function:: template <dag::network_edge EdgeT> \
    dag::network<EdgeT> \
    graph_union(const dag::network<EdgeT>& g1, const dag::network<EdgeT>& g2)

Python:

.. py:function:: dag.graph_union(g1, g2)


Calculates the graph union of two networks :cpp:`g1` and :cpp:`g2`: a new
network containing the union of their sets of vertices and edges.

Cartesian Product
-----------------

C++

.. cpp:function:: template <dag::network_vertex VertT1, \
       dag::network_vertex VertT2> \
    dag::undirected_network<std::pair<VertT1, VertT2>> \
    cartesian_product(\
       const dag::undirected_network<VertT1>& g1, \
       const dag::undirected_network<VertT2>& g2)

Python:

.. py:function:: dag.cartesian_product(\
       g1: dag.undirected_network[vertex_type1], \
       g2: dag.undirected_network[vertex_type2]) \
   -> dag.undirected_network[dag.pair[vertex_type1, vertex_type2]]

Calculates graph cartesian product of two undirected networks :cpp:`g1` and
:cpp:`g1`.

.. note:: While in C++ there are no limits on the types of vertices
   of the network (as long as they satisfy :cpp:concept:`dag::network_vertex`)
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
