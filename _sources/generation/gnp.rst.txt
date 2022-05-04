Random Erdős--Rényi network
===========================

C++:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::uniform_random_bit_generator Gen> \
   dag::undirected_network<VertT> \
   dag::random_gnp_graph(VertT size, double p, Gen& generator)

Python:

.. py:function:: dag.random_gnp_graph[vert_type](size: int, p: float, \
      random_state) \
   -> dag.undirected_network[vert_type]

Generates a random :math:`G(n = size, p)` graph of size :cpp:`size`, where every
edge exists independently with probability :cpp:`p`
:cite:p:`batagelj2005efficient`.

If the parameter :cpp:`p` is not in the :math:`[0, 1]` range, the function fails
by raising a :py:`ValueError` exception in Python or a
:cpp:`std::invalid_argument` exception in C++.
