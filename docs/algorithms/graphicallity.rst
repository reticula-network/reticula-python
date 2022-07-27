Graphicallity
=============

Undirected degree sequence
--------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: is_graphic(degree_seq: List[int]) -> bool

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <std::ranges::forward_range Range> \
        requires degree_range<Range> \
        bool is_graphic(Range&& degree_sequence)

Checks if the sequence can be the degree sequence of a valid undirected graph,
containing no multi-edges or loops, based on the Erdős--Gallai algorithm
:cite:p:`erdos1960graphs,choudum1986simple`.


Directed degree-pair sequence
-----------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: is_digraphic(\
        in_out_degree_sequence: List[Pair[int, int]]) -> bool

  .. tab-tem:: C++
    :sync: cpp

    .. cpp:function:: template <std::ranges::input_range PairRange> \
        requires degree_pair_range<PairRange> \
        bool is_digraphic(PairRange&& in_out_degree_sequence)


Checks if the sequence can be the degree-pair sequence of a valid directed
graph, containing no multi-edges or loops, based on the algorithm by Kleitman
and Wang :cite:p:`kleitman1973algorithms`.

A degree pair sequence is a range (list) of pairs (2-tuples) of integers,
where the first element of each item represents in-degree and the second item
out-degree of one vertex.
