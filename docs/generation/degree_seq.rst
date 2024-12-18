Random degree-sequence network
==============================

Undirected degree-sequence network
----------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_degree_sequence_graph[vert_type](\
          degree_sequence: List[int], random_state) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::ranges::forward_range Range, \
          std::uniform_random_bit_generator Gen> \
       requires \
          degree_range<Range> && \
          std::convertible_to<std::ranges::range_value_t<Range>, VertT> \
       undirected_network<VertT> \
       random_degree_sequence_graph(\
          Range& degree_sequence, Gen& generator)

Generates a random undirected network where the degree sequence of vertices is
exactly equal to the input :cpp:`degree_sequence`. The output network has the
same number of nodes as the length of the :cpp:`degree_sequence`.

If the input :cpp:`degree_sequence` is not graphical, i.e., it is not possible
to create a graph that produces that sequence, the function fails by raising a
:py:`ValueError` exception in Python or a :cpp:`std::invalid_argument`
exception in C++.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> ret.random_degree_sequence_graph[ret.int64](
  ...       degree_sequence=[2, 2, 1, 1], random_state=gen)
  <undirected_network[int64] with 4 verts and 3 edges>

The implementation is based on Ref. :cite:`bayati2010sequential`.

The generation of a random degree-sequence graph becomes more and more
difficult as the density increases. In C++, you can use the `try_` variant of
this function to limit runtime to a limited set of tries:

.. cpp:function:: template <\
      integer_network_vertex VertT, \
      std::ranges::forward_range Range, \
      std::uniform_random_bit_generator Gen> \
   requires \
      degree_range<Range> && \
      std::convertible_to<std::ranges::range_value_t<Range>, VertT> \
   std::optional<undirected_network<VertT>> \
   try_random_degree_sequence_graph(\
      Range& degree_sequence, Gen& generator, std::size_t max_tries)

If this function succeeds in :cpp:`max_tries` tries, it will return the
resulting network, otherwise it returns an instance of :cpp:`std::nullopt_t`.


Directed degree-sequence network
--------------------------------


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_directed_degree_sequence_graph[vert_type](\
          in_out_degree_sequence: List[Tuple[int, int]], random_state) \
       -> directed_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::ranges::forward_range PairRange, \
          std::uniform_random_bit_generator Gen> \
       requires \
          degree_pair_range<PairRange> && \
          is_pairlike_of<std::ranges::range_value_t<PairRange>, VertT, VertT> \
       directed_network<VertT> \
       random_directed_degree_sequence_graph(\
          PairRange& in_out_degree_sequence, Gen& generator)

Similar to the case of `random degree-sequence network`_, the directed variant
creates a graph that reproduces the input :cpp:`in_out_degree_sequence` for in-
and out-degrees. The input :cpp:`in_out_degree_sequence` has to be a range of
pair-like objects, for example a vector of pairs
(:cpp:`std::vector<std::pair<VertT, VertT>>`) or a list of :py:`int` 2-tuple in
Python.

If the input :cpp:`in-out-degree_sequence` is not di-graphical, i.e., it is not
possible to create a directed graph that produces that in- and out-degree
sequence, the funciton fails by raising a :py:`ValueError` exception in Python
or a :cpp:`std::invalid_argument` exception in C++.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> ds = [(0, 0), (2, 0), (0, 1), (1, 1), (0, 2), (1, 0)]
  >>> ret.random_directed_degree_sequence_graph[ret.int64](
  ...       in_out_degree_sequence=ds, random_state=gen)
  <directed_network[int64] with 6 verts and 4 edges>

The implementation is based on an extension of Ref.
:cite:p:`bayati2010sequential`.

Similar to `undirected degree-sequence network`_, this function also provides a
`try_` variant in C++:

.. cpp:function:: template <\
      integer_network_vertex VertT, \
      std::ranges::forward_range PairRange, \
      std::uniform_random_bit_generator Gen> \
   requires \
      degree_pair_range<PairRange> && \
      is_pairlike_of<std::ranges::range_value_t<PairRange>, VertT, VertT> \
   std::optional<directed_network<VertT>> \
   try_random_degree_sequence_graph(\
      PairRange& in_out_degree_sequence, Gen& generator, \
      std::size_t max_tries)

If this function succeeds in :cpp:`max_tries` tries, it will return the
resulting network, otherwise it returns an instance of :cpp:`std::nullopt_t`.
