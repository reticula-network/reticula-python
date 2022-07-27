Graph properties
================

Density
-------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: density(network) -> float

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_vertex VertT> \
      double density(const undirected_network<VertT>& net);

    .. cpp:function:: template <network_vertex VertT> \
      double density(const directed_network<VertT>& net);


Calculates density of a static, dyadic graph.

Density of an undirected network is the number of edges divided by the number of
possible unordered pairs of distinct vertices.

Density of a directed graph is the number of edges divided by the number of
possible ordered pairs of distinct vertices.

Note that in the presense of self-links, density might be higher than 1.
