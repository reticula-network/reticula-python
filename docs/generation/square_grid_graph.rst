Square grid graphs
==================

C++:

.. cpp:function:: template <dag::integer_vertex VertT> \
   dag::undirected_network<VertT> \
   dag::square_grid_graph(VertT side, std::size_t dims, bool periodic = false)

Python:

.. py:function:: dag.square_grid_graph[vert_type](\
      side: int, dims: int, periodic: bool = False) \
   -> dag.undirected_network[vert_type]

Generates a :cpp:`dims`-dimensional square grid lattice with :cpp:`side` vertices
to each side, creating a network of :math:`side^{dims}` vertices. The parameter
:cpp:`periodic` controls the boundary conditions of the lattice.
