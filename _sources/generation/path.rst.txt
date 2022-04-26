Path Graphs
===========


.. cpp:function:: template <integer_vertex VertT> \
   dag::undirected_network<VertT> \
   dag::path_graph(VertT size, bool periodic = false)

.. py:function:: dag.path_graph[vert_type](size: int, periodic: bool = False) \
   -> dag.undirected_network[vert_type]


Generates a chain of `size` vertices, each connected consecutively to each
other. If the periodic parameter is set to `True`, then the first and the last
vertices are also connected, making it into a ring.
