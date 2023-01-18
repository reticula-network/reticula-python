Graph operations
================

Edge induced subgraphs
----------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: edge_induced_subgraph(net, edges)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range Range> \
        requires std::same_as<std::ranges::range_value_t<Range>, EdgeT> \
        network<EdgeT> \
        edge_induced_subgraph(const network<EdgeT>& net, Range&& edges)

Returns a copy of a subset of the network :cpp:`net` consisting only of edges
:cpp:`edges` and all their incident vertices.

Vertex induced subgraphs
------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: vertex_induced_subgraph(net, verts)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range Range> \
        requires std::same_as<std::ranges::range_value_t<Range>, EdgeT::VetexType> \
        network<EdgeT> \
        vertex_induced_subgraph(const network<EdgeT>& net, Range&& verts)

Returns a copy of a subset of the network :cpp:`net` consisting only of vertices
:cpp:`verts` and any edges with all incident vertices in :cpp:`verts`.


Adding and removings edges
--------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: with_edges(network, edges)


  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range EdgeRange> \
        requires std::same_as<std::ranges::range_value_t<EdgeRange>, EdgeT> \
        network<EdgeT> \
        with_edges(const network<EdgeT>& net, EdgeRange&& edges)

Returns a copy of :cpp:`net` with edges from :cpp:`edges` along with all their
incident vertices added in.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: without_edges(network, edges)


  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range EdgeRange> \
        requires std::same_as<std::ranges::range_value_t<EdgeRange>, EdgeT> \
        network<EdgeT> \
        without_edges(const network<EdgeT>& net, EdgeRange&& edges)

Returns a copy of :cpp:`net` with edges from :cpp:`edges` removed. The returned
graph has all the vertices of the original graph.


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


Adding and removing vertices
----------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: with_vertices(network, verts)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range VertRange> \
        requires std::same_as<std::ranges::range_value_t<VertRange>,\
          EdgeT::VetexType> \
        network<EdgeT> \
        with_vertices(const network<EdgeT>& net, VertRange&& verts)

Returns a copy of :cpp:`net` with vertices from :cpp:`verts` added in.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: without_vertices(network, verts)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT, \
          std::ranges::input_range VertRange> \
        requires std::same_as<std::ranges::range_value_t<VertRange>,\
          EdgeT::VetexType> \
        network<EdgeT> \
        without_vertices(const network<EdgeT>& net, VertRange&& verts)

Returns a copy of :cpp:`net` with vertices from :cpp:`verts`, along with all
their incident edges removed.

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


Graph Union
-----------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: graph_union(g1, g2)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
        network<EdgeT> \
        graph_union(const network<EdgeT>& g1, const network<EdgeT>& g2)


Calculates the graph union of two networks :cpp:`g1` and :cpp:`g2`: a new
network containing the union of their sets of vertices and edges.

Cartesian Product
-----------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: cartesian_product(\
          g1: undirected_network[vertex_type1], \
          g2: undirected_network[vertex_type2]) \
      -> undirected_network[pair[vertex_type1, vertex_type2]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_vertex VertT1, \
          network_vertex VertT2> \
        undirected_network<std::pair<VertT1, VertT2>> \
        cartesian_product(\
          const undirected_network<VertT1>& g1, \
          const undirected_network<VertT2>& g2)

Calculates graph cartesian product of two undirected networks :cpp:`g1` and
:cpp:`g1`.

.. note:: While in C++ there are no limits on the types of vertices
   of the network (as long as they satisfy :cpp:concept:`network_vertex`)
   the Python binding only supports certain :ref:`vertex types <vertex-types>`.
   This function is not implemented for cases that would produce output vertices
   too complex to be predefined, i.e., when :py:`vertex_type1` or
   :py:`vertex_type2` are not a simple numerical or string type. In these cases
   you might want to relabel the vertices of the networks before calling this
   function.


Relabling vertices
------------------

.. warning:: Experimental API. We are still trying to find the right balance
  with these functions. The function name, parameters and available variations
  will probably change in the future versions.
