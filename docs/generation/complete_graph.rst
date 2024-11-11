Complete graphs
===============

Undirected complete graph
-------------------------

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

.. code-block:: pycon

   >>> import reticula as ret
   >>> ret.complete_graph[ret.int64](size=128)
   <undirected_network[int64] with 128 verts and 8128 edges>


Complete directed graph
-----------------------

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

.. code-block:: pycon

   >>> import reticula as ret
   >>> ret.complete_directed_graph[ret.int64](size=128)
   <directed_network[int64] with 128 verts and 16256 edges>
