Random expected degree-sequence network
=======================================

C++:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::ranges::forward_range Range, \
      std::uniform_random_bit_generator Gen> \
   requires \
      dag::weight_range<Range> \
   dag::undirected_network<VertT> \
   dag::random_expected_degree_sequence_graph(\
      const Range& weight_sequence, Gen& generator)

Python:

.. py:function:: dag.random_expected_degree_sequence_graph[vert_type](
      weight_sequence: List[float], random_state) \
   -> dag.undirected_network[vert_type]

Generates a graph with the given weight-sequence, more specifically known as
"Chung-Lu graphs" :cite:p:`chung2002connected`. As the network size increases,
as determined by the length of the parameter :cpp:`weight_sequence`, the degree
sequence of generated network approaches on average to the set of numbers in the
parameter :cpp:`weight_sequence`. Existance of each two edges are independent of
each other. The implementation is based on Ref. :cite:p:`miller2011efficient`.

The paramter :cpp:`weight_sequence` is expected to be a list of numericals, e.g.
:cpp:`std::vector<double>` in C++ and :py:`List[float]` in python.

Random expected directed degree-sequence network
================================================

C++:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::ranges::forward_range PairRange, \
      std::uniform_random_bit_generator Gen> \
   requires \
      dag::weight_pair_range<Range> \
   dag::undirected_network<VertT> \
   dag::random_directed_expected_degree_sequence_graph(\
      const PairRange& in_out_weight_sequence, Gen& generator)

Python:

.. py:function:: dag.random_directed_expected_degree_sequence_graph[vert_type](
      in_out_weight_sequence: List[float, float], random_state) \
   -> dag.undirected_network[vert_type]

Similar to the `random expected degree-sequence network`_, this function
generates a directed graph with the given weight-sequence which for large graphs
produce the given weight-sequence as its in- and out-degree sequence. The
implementation is likewise based of the Chung--Lu algorithm
:cite:p:`chung2002connected,miller2011efficient`, extended to directed graphs.
