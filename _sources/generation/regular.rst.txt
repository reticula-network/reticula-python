Random k-regular network
========================

C++:

.. cpp:function:: template <\
      integer_vertex VertT, \
      std::uniform_random_bit_generator Gen> \
   undirected_network<VertT> \
   random_regular_graph(VertT size, VertT degree, Gen& generator)

Python:

.. py:function:: random_barabasi_albert_graph[vert_type](\
      size: int, degree: int, random_state) \
   -> undirected_network[vert_type]

Generates a random :math:`k`-regular network, a random sample out of the space
of all graphs where all nodes have exactly degree equal to :cpp:`degree`.

The generation of a random :math:`k`-regular graph becomes more and more
difficult as the density increases. In C++, you can use the :code:`try_`
variant of this function to limit runtime to a limited set of tries:

.. cpp:function:: template <\
      integer_vertex VertT, \
      std::uniform_random_bit_generator Gen> \
   std::optional<undirected_network<VertT>> \
   try_random_regular_graph(VertT size, VertT degree, Gen& generator, \
      std::size_t max_tries)

If this function succeeds in :cpp:`max_tries` tries, it will return the
resulting network, otherwise it returns an instance of :cpp:`std::nullopt_t`.
