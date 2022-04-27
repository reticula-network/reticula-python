Graphicallity
=============

C++:

.. cpp:function:: template <std::ranges::forward_range Range> \
    requires dag::degree_range<Range> \
    bool is_graphic(const Range& degree_sequence)


Python:

.. py:function:: dag.is_graphic(degree_seq: List[int]) -> bool


Digraphicallity
===============


C++:

.. cpp:function:: template <std::ranges::input_range PairRange> \
    requires dag::degree_pair_range<PairRange> \
    bool is_digraphic(const PairRange& in_out_degree_sequence)


Python:

.. py:function:: dag.is_digraphic(in_out_degree_sequence: List[int, int]) \
    -> bool
