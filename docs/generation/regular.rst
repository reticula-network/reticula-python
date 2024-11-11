Random k-regular network
========================

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_regular_graph[vert_type](\
          size: int, degree: int, random_state) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::uniform_random_bit_generator Gen> \
       undirected_network<VertT> \
       random_regular_graph(VertT size, VertT degree, Gen& generator)

Generates a random :math:`k`-regular network, a random sample out of the space
of all graphs where all nodes have exactly degree equal to :cpp:`degree`.

.. code-block:: pycon

  >>> import reticula as ret
  >>> gen = ret.mersenne_twister(42)
  >>> ret.random_regular_graph[ret.int64](size=128, degree=4, random_state=gen)
  <undirected_network[int64] with 128 verts and 256 edges>

The generation of a random :math:`k`-regular graph becomes more and more
difficult as the density increases. In C++, you can use the :code:`try_`
variant of this function to limit runtime to a limited set of tries:

.. cpp:function:: template <\
      integer_network_vertex VertT, \
      std::uniform_random_bit_generator Gen> \
   std::optional<undirected_network<VertT>> \
   try_random_regular_graph(VertT size, VertT degree, Gen& generator, \
      std::size_t max_tries)

If this function succeeds in :cpp:`max_tries` tries, it will return the
resulting network, otherwise it returns an instance of :cpp:`std::nullopt_t`.
