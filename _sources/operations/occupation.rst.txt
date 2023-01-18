Occupation operations
=====================


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: occupy_edges(network, \
      prob_func: Callable[[network.edge_type()], float], \
      random_state)


  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        std::invocable<const EdgeT&> ProbFun, \
        std::uniform_random_bit_generator Gen>\
      requires std::convertible_to<\
        std::invoke_result_t<ProbFun, const EdgeT&>, double> \
      network<EdgeT> \
      occupy_edges(\
          const network<EdgeT>& g, \
          ProbFun&& occupation_prob, \
          Gen& gen)


Return a copy of the network with the same set of vertices, but with each edge
kept with probability determined by calling the function :py:`prob_func`, or
:cpp:`occupation_prob` in C++.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: occupy_edges(network, \
      prob_map: dict[network.edge_type(), float], \
      random_state, \
      default_prob : float = 0.0)
      :noindex:

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        mapping<EdgeT, double> ProbMapT, \
        std::uniform_random_bit_generator Gen> \
      network<EdgeT> \
      occupy_edges(\
          const network<EdgeT>& g, \
          const ProbMapT& prob_map, \
          Gen& gen, \
          double default_prob = 0.0)


Return a copy of the network with the same set of vertices, but with each edge
kept with probability determined by looking up the edge in the dictionary
:py:`prob_map`. If the edge is not in the map, the value :py:`default_prob` is
determines the probability of the edge being present in the output network.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: uniformly_occupy_edges(network, \
      occupation_prob: float, random_state)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        std::uniform_random_bit_generator Gen>\
      network<EdgeT> \
      uniformly_occupy_edges(\
          const network<EdgeT>& g, \
          double occupation_prob, \
          Gen& gen)


Return a copy of the network with the same set of vertices, but with each edge
kept with probability determined by the parameter :py:`occupation_prob`.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: occupy_vertices(network, \
      prob_func: Callable[[network.vertex_type()], float], random_state)


  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        std::invocable<const typename EdgeT::VertexType&> ProbFun, \
        std::uniform_random_bit_generator Gen>\
      requires std::convertible_to<\
        std::invoke_result_t<ProbFun, const typename EdgeT::VertexType&>, double> \
      network<EdgeT> \
      occupy_vertices(\
          const network<EdgeT>& g, \
          ProbFun&& occupation_prob, \
          Gen& gen)


Return a copy of the network with each vertex (and all its incident edges)
kept with probability determined by calling the function :py:`prob_func`, or
:cpp:`occupation_prob` in C++, with that vertex.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: occupy_vertices(network, \
      prob_map: dict[network.vertex_type(), float], \
      random_state, \
      default_prob : float = 0.0)
      :noindex:

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        mapping<typename EdgeT::VertexType, double> ProbMapT, \
        std::uniform_random_bit_generator Gen> \
      network<EdgeT> \
      occupy_vertices(\
          const network<EdgeT>& g, \
          const ProbMapT& prob_map, \
          Gen& gen, \
          double default_prob = 0.0)

Return a copy of the network with each vertex kept with probability determined
by looking up the vertex in the dictionary :py:`prob_map`. If the vertex is not
in the map, the value :py:`default_prob` is determines the probability of the
vertex being present in the output network.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: uniformly_occupy_vertices(network, \
      occupation_prob: float, random_state)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        std::uniform_random_bit_generator Gen>\
      network<EdgeT> \
      uniformly_occupy_vertices(\
          const network<EdgeT>& g, \
          double occupation_prob, \
          Gen& gen)


Return a copy of the network with each vertex kept with probability determined
by the parameter :py:`occupation_prob`.
