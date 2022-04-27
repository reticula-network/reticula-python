Random Barabási--Albert network
===============================

C++:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::uniform_random_bit_generator Gen> \
   dag::undirected_network<VertT> \
   dag::random_barabasi_albert_graph(VertT n, VertT m, Gen& generator)

Python:

.. py:function:: dag.random_barabasi_albert_graph[vert_type](\
      n: int, p: float, random_state) \
   -> dag.undirected_network[vert_type]

Generates a random Barabási--Albert network
:cite:p:`barabasi1999emergence` of size :cpp:`n`, vertices are added
one-by-one and each vertex is connected to :cpp:`m` random existing vertices.

The parameter :cpp:`m` needs to be smaller than :cpp:`n` and larger than or
equal to 1, otherwise the the function fails by raising a :py:`ValueError`
exception in Python or a :cpp:`std::invalid_argument` exception in C++.
