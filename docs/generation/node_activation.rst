Node activation temporal network
================================

With residual time distribution
-------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_node_activation_temporal_network(base_net, max_t, \
         iet_dist, res_dist, random_state, size_hint: int = 0)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template < \
       temporal_network_edge EdgeT, \
       typename ActivationF, \
       typename ResActivationF, \
       std::uniform_random_bit_generator Gen> \
       network<EdgeT> random_node_activation_temporal_network(\
       const network<typename EdgeT::StaticProjectionType>& base_net, \
       typename EdgeT::TimeType max_t, \
       ActivationF&& inter_event_time_edge_activation, \
       ResActivationF&& residual_time_edge_activation, \
       Gen& generator, std::size_t size_hint = 0)

Generates a random node-activation temporal network by activating a each vertex
of :cpp:`base_net` first according to the residual time distribution (for the
first activation time) then based on the inter-event time distribution, for
time values from 0 to :cpp:`max_t` (exclusive). At each activation, a random
edge (out-)incident to that vertex is selected uniformly at random, and that
edge is activated.

See the list of distributions :ref:`in the relevant section of the documentation
<randomness:Distributions>`.

The output type depends on the type of :py:`base_net`. If a (un)directed network
or a (un)directed hypernetwork is provided, the output will be a (un)directed
temporal network or a (un)directed temporal hypernetwork.

With burn-in
------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_node_activation_temporal_network(base_net, max_t, \
         iet_dist, random_state, size_hint: int = 0)
       :no-index:

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template < \
        temporal_network_edge EdgeT, \
        typename ActivationF, \
        std::uniform_random_bit_generator Gen> \
        network<EdgeT> random_node_activation_temporal_network(\
        const network<typename EdgeT::StaticProjectionType>& base_net, \
        typename EdgeT::TimeType max_t, \
        ActivationF&& inter_event_time_edge_activation, \
        Gen& generator, std::size_t size_hint = 0)

Generates a random node-activation temporal network without a residual time
distribution, by burning-in the inter-event time distribution for :cpp:`max_t`
time before recording events. The output events have times values from 0 to
:cpp:`max_t` (exclusive).

Each vertex of :cpp:`base_net` is activated based on the inter-event time
distribution. At each activation, a random edge (out-)incident to that vertex
is selected uniformly at random, and that edge is activated.


See the list of distributions :ref:`in the relevant section of the documentation
<randomness:Distributions>`.

.. warning::
   This approach might not work on all distributions. It is up to the user to think
   about whether this suits their use case.
