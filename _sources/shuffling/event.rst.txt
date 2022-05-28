Event shuffling
===============

Instant-event shuffling
-----------------------

C++:

.. cpp:function:: template <temporal_edge edget, \
      std::uniform_random_bit_generator gen> \
      requires is_dyadic_v<edget> \
      network<edget> \
      microcanonical_reference_models::instant_event_shuffling(\
         const network<edget>& temp, gen& generator);


Python:

.. py:function:: microcanonical_reference_models.instant_event_shuffling(\
      temporal_network, random_state)

Produces a random shuffling of the temporal network where each event is
attributed to two randomly selected vertices from the original network.
Equivalent to micocanonical reference model with the canonical name
:math:`P[E]`.  The set of vertices, timestamps and the number of events are
conserved.
