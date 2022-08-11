Event graphs
============

Event graphs are an alternative representation of temporal networks as directed
acyclic graphs :cite:p:`kivela2018mapping,mellor2019event`. In this
representation, each temporal network event is represented as a vertex, and two
of these events are connected by a directed link if the first event is adjacent
to the second one.

Event graphs can be used to calculate various reachability properties of
temporal networks :cite:p:`kivela2018mapping,badie2022short,badie2022long`. For
example, the out-component of each vertex in the event graph, which corresponds
to one of the events of the temporal network, can help us understand the set of
reachable temporal network vertices starting from that event
:cite:p:`badie2020efficient`.

Reticula currently provides two ways of studying temporal networks using their
event graph representation:

#. You can :ref:`explicitly calculate the event graph representation of a
   temporal network <Explicit event graph>`. This potentially requires a lot of
   memory, but returns a normal directed network where each vertex happens to
   be an event. You can then bring all the tools available in Reticula for
   working with directed networks to bear.
#. Alternatively, you can construct an :ref:`implicit event graph <Implicit
   event graph>`. This does not require much more memory than the original
   temporal network but limits you to direct use or to certain functions that
   can accept an implicit event graph object.

Explicit event graph
--------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: event_graph(temporal_network, temporal_adjacency) -> \
        directed_network[temporal_network.edge_type()]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
          temporal_adjacency::temporal_adjacency AdjT> \
        directed_network<EdgeT> \
        event_graph(const network<EdgeT>& temp, const AdjT& adj)


This function receives a temporal network and a :ref:`temporal adjacency
object <algorithms/temporal_network_reachability:temporal adjacency>` and
constructs a directed event graph where an event is connected to every other
adjacent event.

.. note:: The constructed event graph is often quite large, even for relatively
  small temporal networks. This function is best used for constrained
  temporal adjacency (e.g., limited waiting-time) or for very small temporal
  networks.

Implicit event graph
--------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: make_implicit_event_graph(\
        temporal_network, temporal_adjacency) -> \
        implicit_event_graph[\
          temporal_network.edge_type(), \
          type(temporal_adjacency::temporal_adjacency)]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
          temporal_adjacency::temporal_adjacency AdjT> \
        implicit_event_graph<EdgeT, AdjT> \
        make_implicit_event_graph(const network<EdgeT>& temp, const AdjT& adj)

This function, similar to the case of the :ref:`explicit event graph`, receives
a temporal network and a :ref:`temporal adjacency object
<algorithms/temporal_network_reachability:temporal adjacency>` and constructs
a implicit event graph object. You can then pass this object to various
function that are designed to receive one.

Implicit event graph functions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: in_component(implicit_event_graph, root) -> \
        component[type(root)]

    .. py:function:: out_component(implicit_event_graph, root) -> \
        component[type(root)]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            component<EdgeT> \
            in_component(\
              const implicit_event_graph<EdgeT, AdjT>& eg, \
              const EdgeT& root)

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            component<EdgeT> \
            out_component(\
              const implicit_event_graph<EdgeT, AdjT>& eg, \
              const EdgeT& root)

Calculates the in- or out-component of a single vertex in the event graph, i.e.,
the set of all events that can transmit an effect that was first transmitted by
the event :cpp:`root`.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: in_components(implicit_event_graph) -> \
      List[Tuple[\
        implicit_event_graph.edge_type(), \
        component[implicit_event_graph.edge_type()]]]

    .. py:function:: out_components(implicit_event_graph) -> \
      List[Tuple[\
        implicit_event_graph.edge_type(), \
        component[implicit_event_graph.edge_type()]]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            std::vector<std::pair<EdgeT, component<EdgeT>>> \
            in_components(const implicit_event_graph<EdgeT, AdjT>& eg)

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            std::vector<std::pair<EdgeT, component<EdgeT>>> \
            out_components(const implicit_event_graph<EdgeT, AdjT>& eg)

Calculates the in- or out-component of a every vertex in the event graph, i.e.,
for each event, this function returns the set of all events that can transmit an
effect that was first transmitted by that event. The algorithm is described in
:cite:p:`badie2020efficient`.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: in_component_sizes(implicit_event_graph) -> \
      List[Tuple[\
        implicit_event_graph.edge_type(), \
        component_size[implicit_event_graph.edge_type()]]]

    .. py:function:: out_component_sizes(implicit_event_graph) -> \
      List[Tuple[\
        implicit_event_graph.edge_type(), \
        component_size[implicit_event_graph.edge_type()]]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            std::vector<std::pair<EdgeT, component_size<EdgeT>>> \
            in_component_sizes(const implicit_event_graph<EdgeT, AdjT>& eg)

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            std::vector<std::pair<EdgeT, component_size<EdgeT>>> \
            out_component_sizes(const implicit_event_graph<EdgeT, AdjT>& eg)

Calculates the size and various properties of in- or out-component of a every
vertex in the event graph, i.e., for each event, this function returns the size
of the set of all events that can transmit an effect that was first transmitted
by that event. The algorithm is described in :cite:p:`badie2020efficient`.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: in_component_size_estimates(implicit_event_graph) -> \
      List[Tuple[\
        implicit_event_graph.edge_type(), \
        component_size_estimate[implicit_event_graph.edge_type()]]]

    .. py:function:: out_component_size_estimates(implicit_event_graph) -> \
      List[Tuple[\
        implicit_event_graph.edge_type(), \
        component_size_estimate[implicit_event_graph.edge_type()]]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            std::vector<std::pair<EdgeT, component_size_estimate<EdgeT>>> \
            in_component_size_estimates(\
              const implicit_event_graph<EdgeT, AdjT>& eg)

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            std::vector<std::pair<EdgeT, component_size_estimate<EdgeT>>> \
            out_component_size_estimates(\
              const implicit_event_graph<EdgeT, AdjT>& eg)

Estimate the size and various properties of in- or out-component of a every
vertex in the event graph, i.e., for each event, this function returns the size
estimates for the set of all events that can transmit an effect that was first
transmitted by that event. The algorithm is described in
:cite:p:`badie2020efficient`.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: weakly_connected_component(implicit_event_graph, root) -> \
        component[implicit_event_graph.edge_type()]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            component<EdgeT> \
            weakly_connected_component(\
              const implicit_event_graph<EdgeT, AdjT>& eg, \
              const EdgeT& vert)

Calculates the weakly-connected component of an event graph that contains the
specified event. The weakly-connected components of an event graph describe an
upper-bound on reachability in a network :cite:p:`kivela2018mapping`.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: weakly_connected_components(\
          implicit_event_graph, singletons: bool = True) -> \
        List[component[implicit_event_graph.edge_type()]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
              temporal_adjacency::temporal_adjacency AdjT> \
            std::vector<component<EdgeT>> \
            weakly_connected_components(\
              const implicit_event_graph<EdgeT, AdjT>& eg, \
              bool singletons = true)

Calculates all weakly-connected components of an event graph. The
weakly-connected components of an event graph describe an upper-bound on
reachability in a network :cite:p:`kivela2018mapping`.

The parameter :cpp:`singletons`, defaulting to true, determines if the
weakly-connected components consisting of a single event should be returned.
