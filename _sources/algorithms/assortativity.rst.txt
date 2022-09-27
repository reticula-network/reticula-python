Assortativity
=============

Degree assortativity
--------------------

Undirected networks
^^^^^^^^^^^^^^^^^^^

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: degree_assortativity(undirected_network) -> float

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <static_undirected_edge EdgeT> \
        double degree_assortativity(const network<EdgeT>& net)

Calculates degree assortativity for undirected dyadic and hypergraph static
networks. Assortativity is calculated through Pearson correlation coefficient
over degrees of all pairs of interacting vertices.


Directed networks
^^^^^^^^^^^^^^^^^

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: in_in_degree_assortativity(directed_network) -> float
    .. py:function:: in_out_degree_assortativity(directed_network) -> float
    .. py:function:: out_in_degree_assortativity(directed_network) -> float
    .. py:function:: out_out_degree_assortativity(directed_network) -> float

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <static_directed_edge EdgeT> \
        double in_in_degree_assortativity(const network<EdgeT>& net)
    .. cpp:function:: template <static_directed_edge EdgeT> \
        double in_out_degree_assortativity(const network<EdgeT>& net)
    .. cpp:function:: template <static_directed_edge EdgeT> \
        double out_in_degree_assortativity(const network<EdgeT>& net)
    .. cpp:function:: template <static_directed_edge EdgeT> \
        double out_out_degree_assortativity(const network<EdgeT>& net)

Calculates in-/out-degree assortativity for directed dyadic and hypergraph
static networks. Assortativity is calculated through Pearson correlation
coefficient over degrees of all pairs of interacting vertices.

Numerical attribute assortativity
---------------------------------

Undirected networks
^^^^^^^^^^^^^^^^^^^

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: attribute_assortativity(undirected_network, \
        attribute_fun: Callable[[network.edge_type()], float]) -> float

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <static_undirected_edge EdgeT, \
          std::invocable<const typename EdgeT::VertexType&> AttrFun> \
        requires std::convertible_to<\
          std::invoke_result_t<\
            AttrFun, const typename EdgeT::VertexType&>, double> \
        double attribute_assortativity(\
          const network<EdgeT>& net, \
          AttrFun&& attribute_fun)


Calculates assortativity of the given numerical function for undirected dyadic
and hypergraph static networks. Assortativity is calculated through Pearson
correlation coefficient over the value of the given function over all pairs of
interacting vertices.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: attribute_assortativity(undirected_network, \
        attribute_map: dict[network.edge_type(), float], \
        default_value : float) -> float
      :noindex:

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        mapping<EdgeT, double> MapT> \
      double attribute_assortativity(\
          const network<EdgeT>& net, \
          const MapT& attribute_map, \
          double default_value)

Calculates assortativity of the given mapping of vertices to floating-point
(dictionary) for undirected dyadic and hypergraph static networks. Assortativity
is calculated through Pearson correlation coefficient over the value of the
given mapping over all pairs of interacting vertices. If a vertex is not present
in the mapping, the value of the argument :cpp:`default_value` is used.


Directed networks
^^^^^^^^^^^^^^^^^

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: attribute_assortativity(directed_network, \
        mutator_attribute_fun: Callable[[network.edge_type()], float], \
        mutated_attribute_fun: Callable[[network.edge_type()], float]) -> float

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <static_undirected_edge EdgeT, \
          std::invocable<const typename EdgeT::VertexType&> AttrFun1,
          std::invocable<const typename EdgeT::VertexType&> AttrFun2> \
        requires
          std::convertible_to<\
            std::invoke_result_t<\
              AttrFun1, const typename EdgeT::VertexType&>, double> && \
          std::convertible_to<\
            std::invoke_result_t<\
              AttrFun2, const typename EdgeT::VertexType&>, double> \
        double attribute_assortativity(\
          const network<EdgeT>& net, \
          AttrFun1&& mutator_attribute_fun, \
          AttrFun2&& mutated_attribute_fun)


Calculates assortativity of the given numerical functions for directed dyadic
and hypergraph static networks. Assortativity is calculated through Pearson
correlation coefficient over the value of the given function over all pairs of
interacting vertices. The associated value of the mutator (tail of the arrow
representation of a directed link) is calculated from the function
:cpp:`mutator_attribute_fun`, and the mutated vertex (head of the arrow) from
:cpp:`mutated_attribute_fun`.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: attribute_assortativity(directed_network, \
        mutator_attribute_map: dict[network.edge_type(), float], \
        mutated_attribute_map: dict[network.edge_type(), float], \
        mutator_default_value : float, \
        mutated_default_value : float) -> float
      :noindex:

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        mapping<EdgeT, double> MapT1, \
        mapping<EdgeT, double> MapT2> \
      double attribute_assortativity(\
          const network<EdgeT>& net, \
          const MapT1& mutator_attribute_map, \
          const MapT2& mutated_attribute_map, \
          double mutator_default_value, \
          double mutated_default_value)

Calculates assortativity of the given pair of mappings of vertices to
floating-point (dictionaries) for directed dyadic and hypergraph static
networks. Assortativity is calculated through Pearson correlation coefficient
over the value of the given pair of mappings over all pairs of interacting
vertices. If a vertex is not present in one of the mappings, the value of the
argument :cpp:`mutator_default_value` or :cpp:`mutated_attribute_fun` is used.
The associated value of the mutator (tail of the arrow representation of a
directed link) is calculated from the function :cpp:`mutator_attribute_fun`, and
the mutated vertex (head of the arrow) from :cpp:`mutated_attribute_fun`.
