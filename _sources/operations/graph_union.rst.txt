Graph union
===========

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: graph_union(g1, g2)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
        network<EdgeT> \
        graph_union(const network<EdgeT>& g1, const network<EdgeT>& g2)


Calculates the graph union of two networks :cpp:`g1` and :cpp:`g2`: a new
network containing the union of their sets of vertices and edges.
