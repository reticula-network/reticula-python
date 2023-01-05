Complete graphs
===============

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: complete_graph[vert_type](size: int) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <integer_network_vertex VertT> \
       undirected_network<VertT> complete_graph(VertT size)


Generates a network of size :cpp:`size` vertices where all possible edges are
present.


Complete directed graphs
========================

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: complete_directed_graph[vert_type](size: int) \
       -> directed_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <integer_network_vertex VertT> \
       directed_network<VertT> complete_directed_graph(VertT size)

Generates a directed network of size :cpp:`size` vertices where all possible
edges are present.
