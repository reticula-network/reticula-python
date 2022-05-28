Timeline Shuffling
==================

Timeline shuffling
------------------

C++:

.. cpp:function:: template <temporal_edge EdgeT, \
      std::uniform_random_bit_generator Gen> \
      requires is_dyadic_v<EdgeT> \
      network<EdgeT> \
      microcanonical_reference_models::timeline_shuffling(\
         const network<EdgeT>& temp, Gen& generator)


Python:

.. py:function:: microcanonical_reference_models.timeline_shuffling(\
      temporal_network, random_state)


Produces a random shuffling of the temporal network where the events are
shuffled by assigning new, uniformly random timetamps and moving it to a
randomly selected link with a non-empty timeline. Equivalent to the
micocanonical reference model with the canonical name :math:`P[\mathcal{L},
E]`.

The set of vertices, total number of events and the static projection of
the temporal network are conserved.

Weight-constrained timeline shuffling
-------------------------------------

.. cpp:function:: template <temporal_edge EdgeT, \
      std::uniform_random_bit_generator Gen> \
      requires is_dyadic_v<EdgeT> \
      network<EdgeT> \
      microcanonical_reference_models::timeline_shuffling(\
         const network<EdgeT>& temp, Gen& generator)

.. cpp:function:: template <temporal_edge EdgeT, \
      std::uniform_random_bit_generator Gen> \
      requires is_dyadic_v<EdgeT> \
      network<EdgeT> \
      microcanonical_reference_models::timeline_shuffling(\
         const network<EdgeT>& temp, Gen& generator, \
         typename EdgeT::TimeType t_start, typename EdgeT::TimeType t_end);


Python:

.. py:function:: microcanonical_reference_models.timeline_shuffling(\
      temporal_network, random_state)

.. py:function:: microcanonical_reference_models.timeline_shuffling(\
      temporal_network, random_state, t_start, t_end)


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

C++:

.. cpp:function:: template <temporal_edge EdgeT, \
      std::uniform_random_bit_generator Gen> \
      requires is_dyadic_v<EdgeT> \
      network<EdgeT> \
      microcanonical_reference_models::activity_constrained_timeline_shuffling(\
         const network<EdgeT>& temp, Gen& generator);

Python:

.. py:function:: \
      microcanonical_reference_models.activity_constrained_timeline_shuffling(\
      temporal_network, random_state)



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

C++:

.. cpp:function:: template <temporal_edge EdgeT, \
      std::uniform_random_bit_generator Gen> \
      requires is_dyadic_v<EdgeT> \
      network<EdgeT> \
      microcanonical_reference_models::inter_event_shuffling(\
         const network<EdgeT>& temp, Gen& generator);


Python:

.. py:function:: microcanonical_reference_models.inter_event_shuffling(\
      temporal_network, random_state)


Produces a random shuffling of the temporal network where the events are
shuffled by shuffling the inter-event times between them, without changing the
static projection link (the vertices) each event is attributed to or the
ordering of events in each timeline. Equivalent to micocanonical reference model
with the canonical name :math:`P[\mathbf{\pi}_\mathcal{L}(\mathbf{\delta \tau}),
\mathbf{t}^1]`.  The set of vertices, cardinality of each timeline, the set of
inter-event times in each timeline and the static projection of the temporal
network are conserved.
