Complete graphs
===============

C++:

.. cpp:function:: template <integer_vertex VertT> \
   undirected_network<VertT> complete_graph(VertT size)

Python:

.. py:function:: complete_graph[vert_type](size: int) \
   -> undirected_network[vert_type]


Generates a network of size :cpp:`size` vertices where all possible edges are
present.


Complete directed graphs
========================

C++:

.. cpp:function:: template <integer_vertex VertT> \
   directed_network<VertT> complete_directed_graph(VertT size)

Python:

.. py:function:: complete_directed_graph[vert_type](size: int) \
   -> directed_network[vert_type]


Generates a directed network of size :cpp:`size` vertices where all possible
edges are present.
