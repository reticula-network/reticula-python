Fully-mixed temporal network
============================

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_fully_mixed_temporal_network[vert_type](\
          size: int, rate: float, max_t: float, random_state) \
       -> undirected_temporal_network[vert_type, double]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::uniform_random_bit_generator Gen> \
       undirected_temporal_network<VertT, double> \
       random_fully_mixed_temporal_network(\
          VertT size, double rate, double max_t, Gen& generator)

Generates a random temporal network of size :cpp:`size` where each link
(connection between two vertices) is activated on times determined by an
exponential inter-event time distribution at constant rate :cpp:`rate`.
