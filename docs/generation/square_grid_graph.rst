Square grid graphs
==================

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: square_grid_graph[vert_type](\
          side: int, dims: int, periodic: bool = False) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <integer_network_vertex VertT> \
       undirected_network<VertT> \
       square_grid_graph(VertT side, std::size_t dims, bool periodic = false)

Generates a :cpp:`dims`-dimensional square grid lattice with :cpp:`side` vertices
to each side, creating a network of :math:`side^{dims}` vertices. The parameter
:cpp:`periodic` controls the boundary conditions of the lattice.

.. code-block:: pycon

   >>> import reticula as ret
   >>> ret.square_grid_graph[ret.int64](side=4, dims=2)
   <undirected_network[int64] with 16 verts and 24 edges>

   >>> ret.square_grid_graph[ret.int64](side=4, dims=2, periodic=True)
   <undirected_network[int64] with 16 verts and 32 edges>
