Event shuffling
===============

Instant-event shuffling
-----------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: microcanonical_reference_models.instant_event_shuffling(\
          temporal_network, random_state)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::instant_event_shuffling(\
          const network<EdgeT>& temp, Gen& generator);


Produces a random shuffling of the temporal network where each event is
attributed to two randomly selected vertices from the original network.
Equivalent to micocanonical reference model with the canonical name
:math:`P[E]`.  The set of vertices, timestamps and the number of events are
conserved.
