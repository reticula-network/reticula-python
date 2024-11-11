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

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> ret.random_fully_mixed_temporal_network[ret.int64](
  ...       size=128, rate=0.1, max_t=1000, random_state=gen)
  <undirected_temporal_network[int64, double] with 128 verts and 812952 edges>
