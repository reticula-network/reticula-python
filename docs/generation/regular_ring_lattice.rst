Regular ring lattice
====================

C++:

.. cpp:function:: template <integer_vertex VertT> \
   undirected_network<VertT> \
   regular_ring_lattice(VertT size, VertT degree)


Python:

.. py:function:: path_graph[vert_type](size: int, degree: int) \
   -> undirected_network[vert_type]

Generates a regular ring lattice of size :cpp:`size` and degree :cpp:`degree`. A
ring-like structure that if arranged in a circle, each vertex would be connected
to :math:`degree/2` vertices before and after it.

The parameter :cpp:`degree` needs to be an even number and :cpp:`degree` needs
to be smaller than :cpp:`size`, otherwise the function fails by raising a
:py:`ValueError` exception in Python or a :cpp:`std::invalid_argument` exception
in C++.
