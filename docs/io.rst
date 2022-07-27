Input/Output and interpolation
==============================

Edgelist input/output
---------------------

Reading an edgelist file
^^^^^^^^^^^^^^^^^^^^^^^^


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: read_edgelist(path: str)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
      network<EdgeT> read_edgelist(std::filesystem::path path)


Dyadic static and temporal networks can be read from space separated files where
each row represents an edge. Note that vertices with no neighbours cannot be
represented in this format.

Writing an edgelist file
^^^^^^^^^^^^^^^^^^^^^^^^


.. tab-set::

  .. tab-item:: Python
    :sync: python

    .. py:function:: write_edgelist(network, path: str)

  .. tab-item:: C++
    :sync: cpp

    .. cpp:function:: template <network_edge EdgeT> \
      void write_edgelist(const network<EdgeT>& g, std::filesystem::path path)

Write a dyadic static and temporal networks in form of space separated files
where each row represents an edge. Note that vertices with no neighbours cannot
be represented in this format.

Interpolation with NetworkX
---------------------------

.. py:function:: to_networkx(network, create_using = None)

  Creates a NetworkX graph from a dyadic static network. If :py:`created_using`
  is not provided, the type of the output is selected based in directionality of
  the input :py:`network`. For directed networks, the output would would be of
  type :py:`networkx.DiGraph`, and for undirected networks it would produce an
  instance of :py:`networkx.Graph`.

  Raises a :py:`NotImplementedError` if NetworkX is not installed or cannot be
  imported at the time Reticula is imported.


.. py:function:: from_networkx[vertex_type](g)

  Creates a dyadic static network from a NetworkX graph. The directedness of the
  network is decided based on whether graph :py:`g` is directed, i.e., whether
  :py:`networkx.is_directed(g)` returns :py:`True`.

  Raises a :py:`NotImplementedError` if networkx is not installed or cannot be
  imported at the time Reticula is imported.
