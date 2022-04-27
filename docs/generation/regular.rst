Random k-regular network
========================

C++:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::uniform_random_bit_generator Gen> \
   dag::undirected_network<VertT> \
   dag::random_regular_graph(VertT size, VertT degree, Gen& generator)

Python:

.. py:function:: dag.random_barabasi_albert_graph[vert_type](\
      size: int, degree: int, random_state) \
   -> dag.undirected_network[vert_type]

Generates a random :math:`k`-regular network, a random sample out of the space
of all graphs where all nodes have exactly degree equal to :cpp:`degree`.

The generation of a random :math:`k`-regular graph becomes more and more
difficult as the density increases. In C++, you can use the `try_` variant of
this function to limit runtime to a limited set of tries:

.. cpp:function:: template <\
      dag::integer_vertex VertT, \
      std::uniform_random_bit_generator Gen> \
   std::optional<dag::undirected_network<VertT>> \
   dag::try_random_regular_graph(VertT size, VertT degree, Gen& generator, \
      std::size_t max_tries)

If this function succeeds in :cpp:`max_tries` tries, it will retrun the
resulting network, otherwise it returns an instance of :cpp:`std::nullopt_t`.
