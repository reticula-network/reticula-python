Regular ring lattice
====================

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: regular_ring_lattice[vert_type](size: int, degree: int) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <integer_network_vertex VertT> \
       undirected_network<VertT> \
       regular_ring_lattice(VertT size, VertT degree)

Generates a regular ring lattice of size :cpp:`size` and degree :cpp:`degree`. A
ring-like structure that if arranged in a circle, each vertex would be connected
to :math:`degree/2` vertices before and after it.

The parameter :cpp:`degree` needs to be an even number and :cpp:`degree` needs
to be smaller than :cpp:`size`, otherwise the function fails by raising a
:py:`ValueError` exception in Python or a :cpp:`std::invalid_argument` exception
in C++.

.. code-block:: pycon

  >>> import reticula as ret
  >>> ret.regular_ring_lattice[ret.int64](size=128, degree=6)
  <undirected_network[int64] with 128 verts and 384 edges>
