Path graphs
===========

C++:

.. cpp:function:: template <dag::integer_vertex VertT> \
   dag::undirected_network<VertT> \
   dag::path_graph(VertT size, bool periodic = false)

Python:

.. py:function:: dag.path_graph[vert_type](size: int, periodic: bool = False) \
   -> dag.undirected_network[vert_type]


Generates a chain of :cpp:`size` vertices, each connected consecutively to each
other. If the periodic parameter is set to :cpp:`true`, then the first and the
last vertices are also connected, making it into a cycle graph equivalent to
what is generated through :cpp:func:`dag::cycle_graph`.
