Graphicallity
=============

C++:

.. cpp:function:: template <std::ranges::forward_range Range> \
    requires dag::degree_range<Range> \
    bool is_graphic(const Range& degree_sequence)


Python:

.. py:function:: dag.is_graphic(degree_seq: List[int]) -> bool

Checks if the sequence can be the degree sequence of a valid undirected graph,
containing no multi-edges or loops, based on the Erdős--Gallai algorithm
:cite:p:`erdos1960graphs,choudum1986simple`.


Digraphicallity
===============


C++:

.. cpp:function:: template <std::ranges::input_range PairRange> \
    requires dag::degree_pair_range<PairRange> \
    bool is_digraphic(const PairRange& in_out_degree_sequence)


Python:

.. py:function:: dag.is_digraphic(in_out_degree_sequence: List[int, int]) \
    -> bool

Checks if the sequence can be the degree sequence of a valid directed graph,
containing no multi-edges or loops, based on the algorithm by Kleitman and Wang
:cite:t:`kleitman1973algorithms`.
