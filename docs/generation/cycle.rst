Cycle graphs
============

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: path_graph[vert_type](size: int) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <integer_vertex VertT> \
       undirected_network<VertT> \
       cycle_graph(VertT size)

Generates a cycle graph of size :cpp:`size`: A 2-regular graph where each vertex
is connected to the one before and after it.
