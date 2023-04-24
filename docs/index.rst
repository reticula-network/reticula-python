Reticula: Temporal network and hypergraphs
==========================================

.. toctree::
   :maxdepth: 2
   :hidden:

   installation
   quickstart
   types
   io
   randomness
   generation/index
   shuffling/index
   operations/index
   algorithms/index
   examples/index
   citing
   bibliography


Reticula is a general purpose C++ library and Python package for fast and
efficient analysis of temporal networks and static and temporal hypergraphs.
Currently, the library supports multiple methods of generating and randomising
networks, using various algorithms to calculate network properties and running
those algorithms safely in a multi-threaded environment.

The names Reticula is the plural form of reticulum, a Latin word meaning network
or a network-like (reticulated) structure.

You can :ref:`install <installation:Installation>` the latest version of the
Python package from the Python Package Index, using the command:

.. code-block:: console

   $ python -m pip install --upgrade reticula

The Python package is available on most relatively modern Linux systems, i.e.,
almost anything released since 2016, running on x64 CPUs. Support for Windows
and MacOS operating systems and the ARM architecture will be introduced in a
future version.

A brief example: Let us generate
:ref:`an Erdős--Rényi network <generation/gnp:Random Erdős--Rényi network>` and
find its :ref:`largest connected component
<algorithms/static_network_reachability:All connected components>`:

.. code-block:: python
   :caption: example.py

   import reticula as ret

   state = ret.mersenne_twister(42)
   g = ret.random_gnp_graph[ret.int64](n=100, p=0.02, random_state=state)

   lcc = ret.largest_connected_component(g)
   print(lcc)

Running this script will print an output like this:

.. code-block:: console

   $ python example.py
   <component[int64] of 93 nodes: {99, 96, ...}>
