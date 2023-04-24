Random Erdős--Rényi network
===========================

Undirected Erdős--Rényi network
-------------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_gnp_graph[vert_type](size: int, p: float, \
          random_state) \
       -> undirected_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::uniform_random_bit_generator Gen> \
       undirected_network<VertT> \
       random_gnp_graph(VertT size, double p, Gen& generator)

Generates a random :math:`G(n = size, p)` graph of size :cpp:`size`, where every
edge exists independently with probability :cpp:`p`
:cite:p:`batagelj2005efficient`.

The expected number of edges is :math:`p \frac{n (n-1)}{2}`.

If the parameter :cpp:`p` is not in the :math:`[0, 1]` range, the function fails
by raising a :py:`ValueError` exception in Python or a
:cpp:`std::invalid_argument` exception in C++.


Directed Erdős--Rényi network
-----------------------------

.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: random_directed_gnp_graph[vert_type](size: int, p: float, \
          random_state) \
       -> directed_network[vert_type]

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <\
          integer_network_vertex VertT, \
          std::uniform_random_bit_generator Gen> \
       directed_network<VertT> \
       random_directed_gnp_graph(VertT size, double p, Gen& generator)


Generates a random directed :math:`G(n = size, p)` graph of size :cpp:`size`,
where every directed edge exists independently with probability :cpp:`p`
:cite:p:`batagelj2005efficient`.

Note that unlike in an undirected network :math:`(i, j)` and :math:`(j, i)`
are distinct edges in a directed network, so the expected number of edges is
:math:`p n (n-1)`

If the parameter :cpp:`p` is not in the :math:`[0, 1]` range, the function fails
by raising a :py:`ValueError` exception in Python or a
:cpp:`std::invalid_argument` exception in C++.
