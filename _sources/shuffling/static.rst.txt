Static Network Link Shuffling
=============================

Degree-sequence preserving shuffling
------------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: microcanonical_reference_models.degree_sequence_preserving_shuffling(\
          static_network, random_state)
    .. py:function:: microcanonical_reference_models.degree_sequence_preserving_shuffling(\
          static_network, random_state, rewires: int)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <undirected_static_network_edgec EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> microcanonical_reference_models::\
          degree_sequence_preserving_shuffling(\
             const network<EdgeT>& temp, Gen& generator)

    .. cpp:function:: template <undirected_static_network_edgec EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> microcanonical_reference_models::\
          degree_sequence_preserving_shuffling(\
             const network<EdgeT>& temp, Gen& generator, std::size_t rewires)

Produces a degree-sequence preserving shuffling of the given undirected static
network. The variant with the ``rewires`` parameter performs the given number
of rewirings. The variant without the ``rewires`` parameter performs a number
of rewirings equal to 100 times the number of edges in the network.


Joint degree-sequence preserving shuffling
==========================================


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: microcanonical_reference_models.joint_degree_sequence_preserving_shuffling(\
          static_network, random_state)
    .. py:function:: microcanonical_reference_models.joint_degree_sequence_preserving_shuffling(\
          static_network, random_state, rewires: int)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <undirected_static_network_edgec EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> microcanonical_reference_models::\
          joint_degree_sequence_preserving_shuffling(\
             const network<EdgeT>& temp, Gen& generator)

    .. cpp:function:: template <undirected_static_network_edgec EdgeT, \
          std::uniform_random_bit_generator Gen> \
          requires is_dyadic_v<EdgeT> \
          network<EdgeT> microcanonical_reference_models::\
          joint_degree_sequence_preserving_shuffling(\
             const network<EdgeT>& temp, Gen& generator, std::size_t rewires)
