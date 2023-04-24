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
