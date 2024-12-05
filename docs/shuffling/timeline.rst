Timeline Shuffling
==================

Timeline shuffling
------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: microcanonical_reference_models.timeline_shuffling(\
          temporal_network, random_state)
       :no-index:

    .. py:function:: microcanonical_reference_models.timeline_shuffling(\
          temporal_network, random_state, t_start, t_end)
       :no-index:

    .. py:function:: microcanonical_reference_models.timeline_shuffling(\
          temporal_network, random_state, unobserved_links: list)
       :no-index:

    .. py:function:: microcanonical_reference_models.timeline_shuffling(\
          temporal_network, random_state, t_start, t_end, unobserved_links: list)
       :no-index:

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::timeline_shuffling(\
             const network<EdgeT>& temp, Gen& generator)

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::timeline_shuffling(\
             const network<EdgeT>& temp, Gen& generator, \
             typename EdgeT::TimeType t_start, typename EdgeT::TimeType t_end);

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::timeline_shuffling(\
             const network<EdgeT>& temp, Gen& generator, \
             const std::vector<typename EdgeT::StaticProjectionType>& \
             unobserved_links);

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::timeline_shuffling(\
             const network<EdgeT>& temp, Gen& generator, \
             typename EdgeT::TimeType t_start, typename EdgeT::TimeType t_end, \
             const std::vector<typename EdgeT::StaticProjectionType>& \
             unobserved_links);


Produces a random shuffling of the temporal network where the events are
shuffled by assigning new, uniformly random timetamps and moving it to a
randomly selected link with a non-empty timeline. Equivalent to the
micocanonical reference model with the canonical name :math:`P[\mathcal{L},
E]`. The observation window, the window where the original measurement of the
temporal network was made, is passed through parameters :cpp:`t_start` and
:cpp:`t_end`.

Alternatively, another variant of the function exist that uses the minimum and
maximum cause time of all the events to automatically set values for parameters
:cpp:`t_start` and :cpp:`t_end`, for cases where information about observation
window is not available.

The observed static projection links in the network are complemented by the set
of links passed through the parameter `unobserved_links`. This is used in case
links are omitted in the static projection of the observed temporal network
that are known to exist from other sources. Essentially, it is assumed that the
links in `unobserved_links` would be present in the static projection of the
temporal network had we had a long enough observation window.

The set of vertices, total number of events and the static projection of
the temporal network are conserved.

Weight-constrained timeline shuffling
-------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: microcanonical_reference_models.weight_constrained_timeline_shuffling(\
          temporal_network, random_state)
          :noindex:

    .. py:function:: microcanonical_reference_models.weight_constrained_timeline_shuffling(\
          temporal_network, random_state, t_start, t_end)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::weight_constrained_timeline_shuffling(\
             const network<EdgeT>& temp, Gen& generator)

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::weight_constrained_timeline_shuffling(\
             const network<EdgeT>& temp, Gen& generator, \
             typename EdgeT::TimeType t_start, typename EdgeT::TimeType t_end);

Produces a random shuffling of the temporal network where the events are
shuffled by assigning new, uniformly random timetamps without changing the
static projection link (the vertices) each event is attributed to. Equivalent
to micocanonical reference model with the canonical name :math:`P[\mathbf{w}]`.
The observation window, the window where the original measurement of the
temporal network was made, is passed through parameters :cpp:`t_start` and
:cpp:`t_end`.

Alternatively, another variant of the function exist that uses the minimum and
maximum cause time of all the events to automatically set values for parameters
:cpp:`t_start` and :cpp:`t_end`, for cases where information about observation
window is not available.

The set of vertices, cardinality of each timeline and the static
projection of the temporal network are conserved.



Activity-constrained timeline shuffling
---------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: \
          microcanonical_reference_models.activity_constrained_timeline_shuffling(\
          temporal_network, random_state)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::activity_constrained_timeline_shuffling(\
             const network<EdgeT>& temp, Gen& generator);

Produces a random shuffling of the temporal network where the events are
shuffled by assigning new, uniformly random timetamps without changing the
static projection link (the vertices) each event is attributed to. The new
timestamps are selected uniformly at random from first cause time to the last
cause time (inclusive) of each timeline. Equivalent to micocanonical reference
model with the canonical name :math:`P[\mathbf{w}, \mathbf{t}^1,
\mathbf{t}^w]`.

The set of vertices, cardinality of each timeline and the static projection of
the temporal network are conserved.


Inter-event shuffling
---------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: microcanonical_reference_models.inter_event_shuffling(\
          temporal_network, random_state)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::inter_event_shuffling(\
             const network<EdgeT>& temp, Gen& generator);

Produces a random shuffling of the temporal network where the events are
shuffled by shuffling the inter-event times between them, without changing the
static projection link (the vertices) each event is attributed to or the
ordering of events in each timeline. Equivalent to micocanonical reference model
with the canonical name :math:`P[\mathbf{\pi}_\mathcal{L}(\mathbf{\delta \tau}),
\mathbf{t}^1]`.  The set of vertices, cardinality of each timeline, the set of
inter-event times in each timeline and the static projection of the temporal
network are conserved.
