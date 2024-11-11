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

.. code-block:: pycon

  >>> import reticula as ret
  >>> g1 = ret.cycle_graph[ret.int64](size=4)
  >>> g2 = ret.complete_graph[ret.int64](size=4)
  >>> g1
  <undirected_network[int64] with 4 verts and 4 edges>
  >>> g2
  <undirected_network[int64] with 4 verts and 6 edges>
  # union of cycle and complete graph is a complete graph
  >>> ret.graph_union(g1, g2)
  <undirected_network[int64] with 4 verts and 6 edges>
