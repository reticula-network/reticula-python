Link activation temporal network
================================

With residual time distribution
-------------------------------

C++:

.. cpp:function:: template < \
    temporal_edge EdgeT, \
    typename ActivationF, \
    typename ResActivationF, \
    std::uniform_random_bit_generator Gen> \
    network<EdgeT> random_link_activation_temporal_network(\
    const network<typename EdgeT::StaticProjectionType>& base_net, \
    typename EdgeT::TimeType max_t, \
    ActivationF&& inter_event_time_edge_activation, \
    ResActivationF&& residual_time_edge_activation, \
    Gen& generator, std::size_t size_hint = 0)

Python:

.. py:function:: random_link_activation_temporal_network(base_net, max_t, \
   iet_dist, res_dist, random_state, size_hint: int = 0)

Generates a random link-activation temporal network by activating the edges in
:cpp:`base_net` first according to the residual time distribution (for the first
activation time) then based on the inter-event time distribution, for time
values from 0 to :cpp:`max_t` (exclusive).

The output type depends on the type of :py:`base_net`. If a (un)directed network
or a (un)directed hypernetwork is provided, the output will be a (un)directed
temporal network or a (un)directed temporal hypernetwork.

With burn-in
------------

C++:

.. cpp:function:: template < \
    temporal_edge EdgeT, \
    typename ActivationF, \
    std::uniform_random_bit_generator Gen> \
    network<EdgeT> random_link_activation_temporal_network(\
    const network<typename EdgeT::StaticProjectionType>& base_net, \
    typename EdgeT::TimeType max_t, \
    ActivationF&& inter_event_time_edge_activation, \
    Gen& generator, std::size_t size_hint = 0)

Python:

.. py:function:: random_link_activation_temporal_network(base_net, max_t, \
   iet_dist, random_state, size_hint: int = 0)

Generates a random link-activation temporal network without a residual time
distribution, by burning-in the inter-event time distribution for :cpp:`max_t`
time before recording events. The output event have times values from 0 to
:cpp:`max_t` (exclusive).

This approach might not work on all distributions. It is up to the user to think
about whether this suits their use case.
