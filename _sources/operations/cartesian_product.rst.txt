Cartesian product
=================

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: cartesian_product(\
          g1: undirected_network[vertex_type1], \
          g2: undirected_network[vertex_type2]) \
      -> undirected_network[pair[vertex_type1, vertex_type2]]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_vertex VertT1, \
          network_vertex VertT2> \
        undirected_network<std::pair<VertT1, VertT2>> \
        cartesian_product(\
          const undirected_network<VertT1>& g1, \
          const undirected_network<VertT2>& g2)

Calculates graph cartesian product of two undirected networks :cpp:`g1` and
:cpp:`g1`.

.. note:: While in C++ there are no limits on the types of vertices
   of the network (as long as they satisfy :cpp:concept:`network_vertex`)
   the Python binding only supports certain :ref:`vertex types <vertex-types>`.
   This function is not implemented for cases that would produce output vertices
   too complex to be predefined, i.e., when :py:`vertex_type1` or
   :py:`vertex_type2` are not a simple numerical or string type. In these cases
   you might want to relabel the vertices of the networks before calling this
   function.
