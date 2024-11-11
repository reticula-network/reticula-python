Assortativity
=============

Assortativity is a measure of preference of nodes to attach to other nodes
similar to themselves. In many cases, researchers are interested in degree
assortaivity, which measures the correlation between the degrees of connected
vertices. However, assortativity can also be calculated for other node attributes :cite:p:`newman2003mixing`.

Reticula provides a set of functions to calculate assortativity in directed
and undirected networks, either in terms of degree or other numerical node
attributes.

.. note ::

  The methods in this section rely on calculating the Pearson correlation
  coefficient between pairs of value sequences. If  all connected vertices
  have equal degree or attribute, or if the network has fewer than two pairs
  of interacting vertices, the result of calculating assortativity will be
  :cpp:`NaN`.


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

    .. cpp:function:: template <undirected_static_network_edge EdgeT> \
        double degree_assortativity(const network<EdgeT>& net)

Calculates degree assortativity for undirected dyadic and hypergraph static
networks. Assortativity is calculated through Pearson correlation coefficient
over degrees of all pairs of interacting vertices.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> net = ret.random_gnp_graph[ret.int64](n=128, p=0.05, random_state=gen)
  >>> ret.degree_assortativity(net)
  0.012174626999704952

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

    .. cpp:function:: template <directed_static_network_edge EdgeT> \
        double in_in_degree_assortativity(const network<EdgeT>& net)
    .. cpp:function:: template <directed_static_network_edge EdgeT> \
        double in_out_degree_assortativity(const network<EdgeT>& net)
    .. cpp:function:: template <directed_static_network_edge EdgeT> \
        double out_in_degree_assortativity(const network<EdgeT>& net)
    .. cpp:function:: template <directed_static_network_edge EdgeT> \
        double out_out_degree_assortativity(const network<EdgeT>& net)

Calculates in-/out-degree assortativity for directed dyadic and hypergraph
static networks. Assortativity is calculated through Pearson correlation
coefficient over degrees of all pairs of interacting vertices.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> net = ret.random_directed_gnp_graph[ret.int64](
  ...             n=128, p=0.05, random_state=gen)
  >>> ret.in_in_degree_assortativity(net)
  -0.008986050522667814
  >>> ret.in_out_degree_assortativity(net)
  -0.05295305364798128

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

    .. cpp:function:: template <undirected_static_network_edge EdgeT, \
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


.. code-block:: pycon

  >>> import reticula as ret
  >>> import math
  >>> gen = ret.mersenne_twister(42)
  >>> net = ret.random_gnp_graph[ret.int64](
  ...       n=128, p=0.05, random_state=gen)
  >>> ret.attribute_assortativity(net,
  ...       lambda v: math.log(ret.degree(net, v)))
  0.018211216997337246


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: attribute_assortativity(undirected_network, \
        attribute_map: dict[network.vertex_type(), float], \
        default_value : float) -> float
      :noindex:

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
        network_edge EdgeT, \
        mapping<VertT, double> MapT> \
      double attribute_assortativity(\
          const network<EdgeT>& net, \
          const MapT& attribute_map, \
          double default_value)

Calculates assortativity of the given mapping of vertices to floating-point
(dictionary) for undirected dyadic and hypergraph static networks.
Assortativity is calculated through Pearson correlation coefficient over the
value of the given mapping over all pairs of interacting vertices. If a vertex
is not present in the mapping, the value of the argument :cpp:`default_value`
is used.


.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> net = ret.random_gnp_graph[ret.int64](
  ...       n=128, p=0.05, random_state=gen)
  >>> attribute_map = {
  ...       v: math.log(ret.degree(net, v))
  ...       for v in net.vertices()}
  >>> ret.attribute_assortativity(net, attribute_map, default_value=0.0)
  0.018211216997337246



Directed networks
^^^^^^^^^^^^^^^^^

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: attribute_assortativity(directed_network, \
        mutator_attribute_fun: Callable[[network.vertex_type()], float], \
        mutated_attribute_fun: Callable[[network.vertex_type()], float]) -> float

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <undirected_static_network_edge EdgeT, \
          std::invocable<const typename EdgeT::VertexType&> AttrFun1, \
          std::invocable<const typename EdgeT::VertexType&> AttrFun2> \
        requires \
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

.. code-block:: pycon

   >>> import reticula as ret
   >>> import math
   >>> gen = ret.mersenne_twister(42)
   >>> net = ret.random_directed_gnp_graph[ret.int64](
   ...       n=128, p=0.05, random_state=gen)
   >>> ret.attribute_assortativity(net,
   ...       lambda tail: math.log(ret.in_degree(net, tail) + 1),
   ...       lambda head: math.log(ret.out_degree(net, head) + 1))
   -0.05753797100756569

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

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> net = ret.random_directed_gnp_graph[ret.int64](
  ...       n=128, p=0.05, random_state=gen)
  >>> mutator_map = {
  ...       tail: math.log(ret.in_degree(net, tail) + 1)
  ...       for tail in net.vertices()}
  >>> mutated_map = {
  ...       head: math.log(ret.out_degree(net, head) + 1)
  ...       for head in net.vertices()}
  >>> ret.attribute_assortativity(net, mutator_map, mutated_map,
  ...       mutator_default_value=0.0, mutated_default_value=0.0)
  -0.05753797100756569
