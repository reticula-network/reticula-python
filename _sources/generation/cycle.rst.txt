Cycle graphs
============

C++:

.. cpp:function:: template <dag::integer_vertex VertT> \
   dag::undirected_network<VertT> \
   dag::cycle_graph(VertT size)


Python:

.. py:function:: dag.path_graph[vert_type](size: int) \
   -> dag.undirected_network[vert_type]

Generates a cycle graph of size :cpp:`size`: A 2-regular graph where each vertex
is connected to the one before and after it.
