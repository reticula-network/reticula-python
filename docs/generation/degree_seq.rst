Random degree-sequence network
==============================

C++:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::ranges::forward_range Range, \
      std::uniform_random_bit_generator Gen> \
   requires \
      dag::degree_range<Range> && \
      std::convertible_to<std::ranges::range_value_t<Range>, VertT> \
   dag::undirected_network<VertT> \
   dag::random_degree_sequence_graph(\
      const Range& degree_sequence, Gen& generator)

Python:

.. py:function:: dag.random_degree_sequence_graph[vert_type](
      degree_sequence: List[int], random_state) \
   -> dag.undirected_network[vert_type]


Generates a random undirected network where the degree sequence of vertices is
exactly equal to the input :cpp:`degree_sequence`. The output network has the
same number of nodes as the length of the :cpp:`degree_sequence`.

If the input :cpp:`degree_sequence` is not graphical, i.e., it is not possible
to create a graph that produces that sequence, the function fails by raising a
:py:`ValueError` exception in Python or a :cpp:`std::invalid_argument` exception
in C++.

The implementation is based on Ref. :cite:`bayati2010sequential`.

The generation of a random degree-sequence graph becomes more and more
difficult as the density increases. In C++, you can use the `try_` variant of
this function to limit runtime to a limited set of tries:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::ranges::forward_range Range, \
      std::uniform_random_bit_generator Gen> \
   requires \
      dag::degree_range<Range> && \
      std::convertible_to<std::ranges::range_value_t<Range>, VertT> \
   std::optional<dag::undirected_network<VertT>> \
   dag::try_random_degree_sequence_graph(\
      const Range& degree_sequence, Gen& generator, std::size_t max_tries)

If this function succeeds in :cpp:`max_tries` tries, it will return the
resulting network, otherwise it returns an instance of :cpp:`std::nullopt_t`.

Random directed degree-sequence network
=======================================


C++:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::ranges::forward_range PairRange, \
      std::uniform_random_bit_generator Gen> \
   requires \
      dag::degree_pair_range<PairRange> && \
      dag::is_pairlike_of<std::ranges::range_value_t<PairRange>, VertT, VertT> \
   dag::directed_network<VertT> \
   dag::random_directed_degree_sequence_graph(\
      const PairRange& in_out_degree_sequence, Gen& generator)

Python:

.. py:function:: dag.random_directed_degree_sequence_graph[vert_type](
      in_out_degree_sequence: List[Tuple[int, int]], random_state) \
   -> dag.directed_network[vert_type]

Similar to the case of `random degree-sequence network`_, the directed variant
creates a graph that reproduces the input :cpp:`in_out_degree_sequence` for in-
and out-degrees. The input :cpp:`in_out_degree_sequence` has to be a range of
pair-like objects, for example a vector of pairs
(:cpp:`std::vector<std::pair<VertT, VertT>>`) or a list of :py:`int` 2-tuple in
Python.

The implementation is based on an extension of Ref.
:cite:p:`bayati2010sequential`.

This function also provides a `try_` variant:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::ranges::forward_range PairRange, \
      std::uniform_random_bit_generator Gen> \
   requires \
      dag::degree_pair_range<PairRange> && \
      dag::is_pairlike_of<std::ranges::range_value_t<PairRange>, VertT, VertT> \
   std::optional<dag::directed_network<VertT>> \
   dag::try_random_degree_sequence_graph(\
      const PairRange& in_out_degree_sequence, Gen& generator, \
      std::size_t max_tries)

If the input :cpp:`in-out-degree_sequence` is not di-graphical, i.e., it is not
possible to create a directed graph that produces that in- and out-degree
sequence, the funciton fails by raising a :py:`ValueError` exception in Python
or a :cpp:`std::invalid_argument` exception in C++.

If this function succeeds in :cpp:`max_tries` tries, it will return the
resulting network, otherwise it returns an instance of :cpp:`std::nullopt_t`.
