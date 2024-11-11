Graph properties
================

Density
-------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: density(network) -> float

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_vertex VertT> \
      double density(const undirected_network<VertT>& net)

    .. cpp:function:: template <network_vertex VertT> \
      double density(const directed_network<VertT>& net)


Calculates density of a static, dyadic graph.

Density of an undirected network is the number of edges divided by the number of
possible unordered pairs of distinct vertices.

Density of a directed graph is the number of edges divided by the number of
possible ordered pairs of distinct vertices.

Note that in the presense of self-links, density might be higher than 1.

.. code-block:: pycon

  >>> import reticula as ret
  >>> g = ret.cycle_graph[ret.int64](size=128)
  >>> ret.density(g)
  0.015748031496062992


Temporal network observation window
-----------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: time_window(temporal_network) -> \
      tuple[temporal_network.time_type(), temporal_network.time_type()]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT> \
      std::pair<typename EdgeT::TimeType, typename EdgeT::TimeType> \
      time_window(const network<EdgeT>& temporal_network)

Finds the range of event times present in the events. If temporal edges have
different cause and effect times (i.e. they have delays) this would be
equivalent to a tuple consisting of the minimum cause time and maximum effect
time. If the events don't have delays, this returns a tuple with the minimum and
the maximum event time.

If the temporal network has no events (edges), this function throws a
:cpp:`std::invalid_argument` in C++ and a :py:`ValueError` in Python.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: cause_time_window(temporal_network) -> \
      tuple[temporal_network.time_type(), temporal_network.time_type()]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT> \
      std::pair<typename EdgeT::TimeType, typename EdgeT::TimeType> \
      cause_time_window(const network<EdgeT>& temporal_network)

Finds the range of event cause times present in the events. If the temporal
network has no events (edges), this function throws a
:cpp:`std::invalid_argument` in C++ and a :py:`ValueError` in Python. If the
temporal network events don't have delays, this is indistinguishable from
:py:func:`time_window`.


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: effect_time_window(temporal_network) -> \
      tuple[temporal_network.time_type(), temporal_network.time_type()]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT> \
      std::pair<typename EdgeT::TimeType, typename EdgeT::TimeType> \
      effect_time_window(const network<EdgeT>& temporal_network)

Finds the range of event effect times present in the events. If the temporal
network has no events (edges), this function throws a
:cpp:`std::invalid_argument` in C++ and a :py:`ValueError` in Python. If the
temporal network events don't have delays, this is indistinguishable from
:py:func:`time_window`.

Static projection of a temporal network
---------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: static_projection(temporal_network)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
      network<typename EdgeT::StaticProjectionType> \
      effect_time_window(const network<EdgeT>& temporal_network)

Returns a static projection (also known as spatial projection or time-aggregate)
of the temporal network. Each event is stripped of it's temporal information,
and a static network of the most appropriate type is formed. For example, a
directed delayed hypergraph temporal network, passed to this function, is
projected into a directed hypergraph.

Temporal network link timelines
-------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: link_timeline(temporal_network, link) -> \
        list[temporal_network.edge_type()]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT> \
      std::vector<EdgeT> \
      link_timeline(\
        const network<EdgeT>& temporal_network, \
        const typename EdgeT::StaticProjectionType& link)

Returns a list of events that correspond to (project to) the static link
:cpp:`link` ordered by cause time of the events.

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: link_timelines(temporal_network) -> \
      list[tuple[temporal_network.edge_type().static_projection_type(), \
          list[temporal_network.edge_type()]]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT> \
      std::vector< \
        std::pair<typename EdgeT::StaticProjectionType, std::vector<EdgeT>>> \
      link_timelines(const network<EdgeT>& temporal_network)

For each link, each static edge in the :ref:`static projection
<algorithms/graph_properties:Static projection of a temporal network>` of the
network, this function returns a list of the events that correspond to
(project to) that link ordered by cause time of the events.
