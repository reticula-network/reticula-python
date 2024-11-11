Random uniform hypergraphs
==========================

Undirected random uniform hypergraph
------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_uniform_hypergraph[vert_type](\
        size: int, edge_degree: int, edge_prob: float, random_state) \
       -> undirected_hypernetwork[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <integer_network_vertex VertT, \
          std::uniform_random_bit_generator Gen> \
       undirected_hypernetwork<VertT> random_uniform_hypergraph(\
         VertT size, VertT edge_degree, double edge_prob, Gen& generator)


Generates a random hypergraph of size :cpp:`size` vertices where each of the
possible edges of degree :cpp:`edge_degree` are present independently with
probability :cpp:`edge_prob`. This is the natural extension of Erdős--Rényi
networks to uniform hypergraphs.

All edges will consist of exactly :cpp:`edge_degree` vertices.

.. code-block:: pycon

   >>> import reticula as ret
   >>> gen = ret.mersenne_twister(42)
   >>> ret.random_uniform_hypergraph[ret.int64](
   ...      size=128, edge_degree=4, edge_prob=0.1, random_state=gen)
   <undirected_hypernetwork[int64] with 128 verts and 1067339 edges>


Directed random uniform hypergraph
----------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_directed_uniform_hypergraph[vert_type](\
        size: int, edge_in_degree: int, edge_out_degree: int, \
        edge_prob: float, random_state) \
       -> directed_hypernetwork[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <integer_network_vertex VertT, \
          std::uniform_random_bit_generator Gen> \
       directed_hypernetwork<VertT> random_directed_uniform_hypergraph(\
         VertT size, VertT edge_in_degree, VertT edge_out_degree, \
         double edge_prob, Gen& generator)

Generates a random hypergraph of size :cpp:`size` vertices where each of the
possible directed edges of in-degree :cpp:`edge_in_degree` and out-degree
:cpp:`edge_out_degree` are present independently with probability
:cpp:`edge_prob`. This is the natural extension of directed Erdős--Rényi
networks to uniform directed hypergraphs.

All edges will consist of exactly :cpp:`edge_in_degree` mutator vertices (tail
of the arrow) and :cpp:`edge_out_degree` mutated vertices (head of the arrow).

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> ret.random_directed_uniform_hypergraph[ret.int64](
  ...       size=128, edge_in_degree=2, edge_out_degree=2,
  ...       edge_prob=0.01, random_state=gen)
  <directed_hypernetwork[int64] with 128 verts and 660286 edges>
