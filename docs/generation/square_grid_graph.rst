Square grid graphs
==================

C++:

.. cpp:function:: template <integer_vertex VertT> \
   undirected_network<VertT> \
   square_grid_graph(VertT side, std::size_t dims, bool periodic = false)

Python:

.. py:function:: square_grid_graph[vert_type](\
      side: int, dims: int, periodic: bool = False) \
   -> undirected_network[vert_type]

Generates a :cpp:`dims`-dimensional square grid lattice with :cpp:`side` vertices
to each side, creating a network of :math:`side^{dims}` vertices. The parameter
:cpp:`periodic` controls the boundary conditions of the lattice.
