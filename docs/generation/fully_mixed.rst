Fully-mixed temporal network
============================

C++:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::uniform_random_bit_generator Gen> \
   dag::undirected_temporal_network<VertT, double> \
   dag::random_fully_mixed_temporal_network(\
      VertT size, double rate, Gen& generator)

Python:

.. py:function:: dag.random_fully_mixed_temporal_network[vert_type](\
      size: int, rate: float, random_state) \
   -> dag.undirected_temporal_network[vert_type, dag.double]

Generates a random temporal network of size :cpp:`size` where each link
(connection between two edges) is activated on times determined by an
exponential inter-event time distribution.
