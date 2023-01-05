Link Shuffling
==============

Link shuffling
--------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: microcanonical_reference_models.link_shuffling(\
          temporal_network, random_state)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> microcanonical_reference_models::link_shuffling(\
             const network<EdgeT>& temp, Gen& generator)


Produces a random shuffling of the temporal network where all events between two
vertices are attributed to two randomly selected vertices from the original
network. Equivalent to micocanonical reference model with the canonical name
:math:`P[p_{\mathcal{L}}(\Theta)]`.

The set of vertices, timestamps, the number of events and the multiset of
timelines are conserved.

Connected link shuffling
------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: microcanonical_reference_models.connected_link_shuffling(\
          temporal_network, random_state)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::connected_link_shuffling(\
            const network<EdgeT>& temp, Gen& generator)

Produces a random shuffling of the temporal network where all events between two
vertices are attributed to two randomly selected vertices from the original
network. As opposed to `Link shuffling`, this model preserves the pattern of
(weak) connectivity in the static projection of the original graph, i.e., the
static projection of the output would have the same set of (weakly) connected
components as the input. Generalisation of the micocanonical reference model
with the canonical name :math:`P[I_\lambda, p_{\mathcal{L}}(\Theta)]` to
temporal networks with directed and/or multi-component static projections.

In addition to the set of components of the static projection, the set of
vertices, timestamps, the number of events and the multiset of timelines
of the temporal network are conserved.

Topology-constrained link shuffling
-----------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: \
          microcanonical_reference_models.topology_constrained_link_shuffling(\
            temporal_network, random_state)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <temporal_network_edge EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> \
          microcanonical_reference_models::topology_constrained_link_shuffling(\
            const network<EdgeT>& temp, Gen& generator)


Produces a random shuffling of the temporal network where the events are
shuffled by assigning new, uniformly random timetamps and moving it to a
randomly selected link with a non-empty timeline. Equivalent to micocanonical
reference model with the canonical name :math:`P[\mathcal{L}, E]`.

The set of vertices, total number of events and the static projection of the
temporal network are conserved.
