Complete graphs
===============

C++:

.. cpp:function:: template <dag::integer_vertex VertT> \
   dag::undirected_network<VertT> dag::complete_graph(VertT size)

Python:

.. py:function:: dag.complete_graph[vert_type](size: int) \
   -> dag.undirected_network[vert_type]


Generates a network of size :cpp:`size` vertices where all possible edges are
present.


Complete directed graphs
========================

C++:

.. cpp:function:: template <dag::integer_vertex VertT> \
   dag::directed_network<VertT> dag::complete_directed_graph(VertT size)

Python:

.. py:function:: dag.complete_directed_graph[vert_type](size: int) \
   -> dag.directed_network[vert_type]


Generates a directed network of size :cpp:`size` vertices where all possible
edges are present.
