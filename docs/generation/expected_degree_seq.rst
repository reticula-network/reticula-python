Random expected degree-sequence network
=======================================

Undirected expected degree-sequence network
-------------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_expected_degree_sequence_graph[vert_type](\
          weight_sequence: List[float], random_state, \
          self_loops: bool = False) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::ranges::input_range Range, \
          std::uniform_random_bit_generator Gen> \
       requires \
          weight_range<Range> \
       undirected_network<VertT> \
       random_expected_degree_sequence_graph(\
          Range&& weight_sequence, Gen& generator, \
          bool self_loops = false)

Generates a graph with the given weight-sequence, more specifically known as
"Chung-Lu graphs" :cite:p:`chung2002connected`. As the network size increases,
as determined by the length of the parameter :cpp:`weight_sequence`, the degree
sequence of generated network approaches on average to the set of numbers in the
parameter :cpp:`weight_sequence`. The existence of each two edges are
independent of each other. The implementation is based on Ref.
:cite:p:`miller2011efficient`.

The parameter :cpp:`weight_sequence` is expected to be a list of numericals,
e.g., :cpp:`std::vector<double>` in C++ and :py:`List[float]` in python. The
parameter :cpp:`self_loops` controls the existance of self loops in the
resulting network and defults to :cpp:`false`.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> g = ret.random_expected_degree_sequence_graph[ret.int64](
  ...            weight_sequence=[2, 2, 1, 1], random_state=gen)
  >>> g
  <undirected_network[int64] with 4 verts and 3 edges>

Note that the degree sequence is not necessarily the same as the input, but
only on expectation!

.. code-block:: pycon

  >>> gen = ret.mersenne_twister(42)
  >>> g = ret.random_expected_degree_sequence_graph[ret.int64](
  ...            weight_sequence=[2, 2, 1, 1], random_state=gen)
  >>> ret.degree_sequence(g)
  [2, 3, 2, 1]
  >>> g = ret.random_expected_degree_sequence_graph[ret.int64](
  ...            weight_sequence=[2, 2, 1, 1], random_state=gen)
  >>> ret.degree_sequence(g)
  [3, 1, 1, 1]


Directed expected degree-sequence network
-----------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_directed_expected_degree_sequence_graph[vert_type](\
          in_out_weight_sequence: List[Tuple[float, float]], random_state, \
          self_loops: bool = False) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::ranges::input_range PairRange, \
          std::uniform_random_bit_generator Gen> \
       requires \
          weight_pair_range<PairRange> \
       undirected_network<VertT> \
       random_directed_expected_degree_sequence_graph(\
          PairRange&& in_out_weight_sequence, Gen& generator, \
          bool self_loops = false)

Similar to the `random expected degree-sequence network`_, this function
generates a directed graph with the given weight-sequence which for large graphs
produce the given weight-sequence as its in- and out-degree sequence. The
implementation is likewise based of the Chung--Lu algorithm
:cite:p:`chung2002connected,miller2011efficient`, extended to directed graphs.

The parameter :cpp:`in_out_weight_sequence` is expected to be a list of pairs of
numericals, e.g., :cpp:`std::vector<std::pair<double, double>>` in C++ and
:py:`List[Tuple[float, float]]` in python, with each element of the list/vector
representing expected in- and out-degree of one vertex.

The parameter :cpp:`self_loops` controls the existance of self loops in the
resulting network and defults to :cpp:`false`.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> g = ret.random_directed_expected_degree_sequence_graph[ret.int64](
  ...            in_out_weight_sequence=[(2, 2), (2, 2), (1, 1), (1, 1)],
  ...            random_state=gen)
  >>> g
  <undirected_network[int64] with 4 verts and 6 edges>
  >>> ret.in_out_degree_pair_sequence(g)
  [(2, 2), (1, 3), (2, 1), (1, 1)]


Undirected expected degree-sequence hypergraph
----------------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_expected_degree_sequence_hypergraph[vert_type](\
          vertex_weight_sequence: List[float], \
          edge_weight_sequence: List[float], random_state) \
       -> undirected_hypernetwork[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::ranges::input_range VertRange, \
          std::ranges::input_range EdgeRange, \
          std::uniform_random_bit_generator Gen> \
       requires \
          weight_range<VertRange> && weight_range<EdgeRange> \
       undirected_hypernetwork<VertT> \
       random_expected_degree_sequence_hypergraph(\
          VertRange&& vertex_weight_sequence, \
          EdgeRange&& edge_weight_sequence, Gen& generator)

Generates a random undirected hypergraph with given weight-sequence for vertex
and edge degrees. The degree of a vertex referes to the number of edges incident
to that vertex, whereas the degree of an edge referes to the number of incident
vertices. The algorithm is based on the "Chung-Lu" method
:cite:p:`chung2002connected`, extended to hypergraphs by generating a random
bipartite incidence network :cite:p:`aksoy2017measuring`. For larger networks,
the vertex degree sequence and the edge degree sequence on expectation apprach
the weight sequences :cpp:`vertex_weight_sequence` and
:cpp:`edge_weight_sequence`.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> ret.random_expected_degree_sequence_hypergraph[ret.int64](
  ...            vertex_weight_sequence=[2, 2, 1, 1],
  ...            edge_weight_sequence=[2, 2, 1, 1],
  ...            random_state=gen)
  <undirected_hypernetwork[int64] with 4 verts and 3 edges>


.. note::

   The algorithm used for this method can produce multi-edges, i.e., edges with
   the exact same set of incident vertices. As the library currently does not
   support multi-edges, only one of each set of multi-edge is represented in
   the output. This should only be a concern for small networks combined with
   many edges with low edge degrees.

   The code also currently might produces an edge with no incident vertices.

   .. code-block:: pycon

     >>> import reticula as ret
     >>> gen = ret.mersenne_twister(42)
     >>> g = ret.random_expected_degree_sequence_hypergraph[ret.int64](
     ...            vertex_weight_sequence=[2, 2, 1, 1],
     ...            edge_weight_sequence=[2, 2, 1, 1],
     ...            random_state=gen)
     >>> ret.ret.degree_sequence(g)
     [2, 2, 0, 1]
     >>> ret.edge_degree_sequence(g)
     [0, 2, 3]

Directed expected degree-sequence hypergraph
----------------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_directed_expected_degree_sequence_hypergraph[vert_type](\
          vertex_in_out_weight_sequence: List[Tuple[float, float]], \
          edge_in_out_weight_sequence: List[Tuple[float, float]], \
          random_state) \
       -> directed_hypernetwork[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::ranges::input_range VertPairRange, \
          std::ranges::input_range EdgePairRange, \
          std::uniform_random_bit_generator Gen> \
       requires \
          weight_pair_range<VertPairRange> && \
          weight_pair_range<EdgePairRange> \
       directed_hypernetwork<VertT> \
       random_expected_degree_sequence_hypergraph(\
          VertPairRange&& vertex_in_out_weight_sequence, \
          EdgePairRange&& edge_in_out_weight_sequence, \
          Gen& generator)

Generates a random directed hypergraph with given in- and out-weight-sequence
for vertex and edge degrees. The in-/out-degree of a vertex referes to the
number of edges in-/out-incident to that vertex, whereas the in-/out-degree of
an edge referes to the number of in-/out-incident vertices. The algorithm is
based on the "Chung-Lu" method :cite:p:`chung2002connected`, extended to
directed hypergraphs by generating a random directed bipartite incidence
network :cite:p:`aksoy2017measuring`. For larger networks, the vertex degree
sequence and the edge degree sequence on expectation apprach the in-/out-weight
sequences :cpp:`vertex_in_out_weight_sequence` and
:cpp:`edge_in_out_weight_sequence`.

The parameters :cpp:`vertex_in_out_weight_sequence` and
:cpp:`edge_in_out_weight_sequence` are expected to be a list of pairs of
numericals, e.g., :cpp:`std::vector<std::pair<double, double>>` in C++ and
:py:`List[Tuple[float, float]]` in python, with each element of the list/vector
representing expected in- and out-degree of one vertex/edge.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> ret.random_directed_expected_degree_sequence_hypergraph[ret.int64](
  ...            vertex_in_out_weight_sequence=[(2, 2), (2, 2), (1, 1), (1, 1)],
  ...            edge_in_out_weight_sequence=[(2, 2), (2, 2), (1, 1), (1, 1)],
  ...            random_state=gen)
  <directed_hypernetwork[int64] with 4 verts and 4 edges>

.. note::

   The algorithm used for this method can produce multi-edges, i.e., edges with
   the exact same set of incident vertices. As the library currently does not
   support multi-edges, only one of each set of multi-edge is represented in
   the output. This should only be a concern for small networks combined with
   many edges with low edge degrees.

   The code also currently might produces an edge with no in- and/or
   out-incident vertices.

   .. code-block:: pycon

    >>> import reticula as ret
    >>> gen = ret.mersenne_twister(42)
    >>> g = ret.random_directed_expected_degree_sequence_hypergraph[ret.int64](
    ...            vertex_in_out_weight_sequence=[(2, 2), (2, 2), (1, 1), (1, 1)],
    ...            edge_in_out_weight_sequence=[(2, 2), (2, 2), (1, 1), (1, 1)],
    ...            random_state=gen)
    >>> ret.in_out_degree_pair_sequence(g)
    [(2, 2), (2, 2), (1, 1), (1, 1)]
    >>> ret.edge_in_out_degree_pair_sequence(g)
    [(0, 2), (3, 3), (4, 2), (2, 0)]
