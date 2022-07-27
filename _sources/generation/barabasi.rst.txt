Random Barabási--Albert network
===============================

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_barabasi_albert_graph[vert_type](\
          n: int, p: float, random_state) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_vertex VertT, \
          std::uniform_random_bit_generator Gen> \
       undirected_network<VertT> \
       random_barabasi_albert_graph(VertT n, VertT m, Gen& generator)

Generates a random Barabási--Albert network
:cite:p:`barabasi1999emergence` of size :cpp:`n`, vertices are added
one-by-one and each vertex is connected to :cpp:`m` random existing vertices.

The parameter :cpp:`m` needs to be smaller than :cpp:`n` and larger than or
equal to 1, otherwise the function fails by raising a :py:`ValueError` exception
in Python or a :cpp:`std::invalid_argument` exception in C++.
