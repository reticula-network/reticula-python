Input/Output and Interpolation
==============================

Edgelist Input/Output
---------------------

..
  TODO: Talk about supported edge types

Reading an edgelist file
^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: template <network_edge EdgeT> \
  network<EdgeT> read_edgelist(std::filesystem::path path, \
    char delimiter = ' ', char quote = '"')

.. py:function:: read_edgelist(path: str, \
  delimiter: str = " ", quote: str = "\"")


Static and temporal networks can be read from edge-list tab, space or comma
separated files.


Writing an edgelist file
^^^^^^^^^^^^^^^^^^^^^^^^

Interpolation with NetworkX
---------------------------

.. py:function:: to_nx(network, create_using = None)

  Creates a NetworkX graph from a dyadic static network. If :py:`created_using`
  is not provided, the type of the output is selected based in directionality of
  the input :py:`network`. For directed networks, the output would would be of
  type :py:`networkx.DiGraph`, and for undirected networks it would produce an
  instance of :py:`networkx.Graph`.
