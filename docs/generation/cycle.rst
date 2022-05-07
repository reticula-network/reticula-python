Cycle graphs
============

C++:

.. cpp:function:: template <integer_vertex VertT> \
   undirected_network<VertT> \
   cycle_graph(VertT size)


Python:

.. py:function:: path_graph[vert_type](size: int) \
   -> undirected_network[vert_type]

Generates a cycle graph of size :cpp:`size`: A 2-regular graph where each vertex
is connected to the one before and after it.
