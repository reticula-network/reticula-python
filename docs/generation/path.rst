Path graphs
===========

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: path_graph[vert_type](size: int, periodic: bool = False) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <integer_vertex VertT> \
       undirected_network<VertT> \
       path_graph(VertT size, bool periodic = false)

Generates a chain of :cpp:`size` vertices, each connected consecutively to each
other. If the periodic parameter is set to :cpp:`true`, then the first and the
last vertices are also connected, making it into a cycle graph equivalent to
what is generated through :cpp:func:`cycle_graph`.
