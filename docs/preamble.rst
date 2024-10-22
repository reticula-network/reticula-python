Reticula is a general purpose Python package backed by a powerful C++ library
for fast and efficient analysis of **temporal networks** and **static and
temporal hypergraphs**. Currently, the library supports multiple methods of
generating and randomising networks, using various algorithms to calculate
network properties and running those algorithms safely in a multi-threaded
environment.

The names Reticula is the plural form of reticulum, a Latin word meaning
network or a network-like (reticulated) structure.

You can :ref:`install <installation:Python binding>` the latest version of the
Python package from the Python Package Index, using the command:

.. code-block:: console

   $ python -m pip install --upgrade reticula

The Python package is available on most relatively modern Windows, MacOS and
Linux systems. MacOS package provides universal binaries supporting both ARM
and x64 hardware. Support for the ARM architecture on Windows and Linux will be
introduced in future versions.

Example: Temporal network reachability
--------------------------------------

Let us generate a :doc:`random link activation temporal network
<generation/link_activation>` from a :doc:`random regular static base network
<generation/regular>` and poisson process link activations and analyse
reachability from a specific node at a specific time to all other nodes and
times:

.. code-block:: python

   import reticula as ret

   # random number generator:
   gen = ret.mersenne_twister(42)

   # make a random regular static base netowrk with integer vertices:
   g = ret.random_regular_graph[ret.int64](size=100, degree=4, random_state=gen)

   print(g)
   # -> <undirected_network[int64] with 100 verts and 200 edges>

   # make a Poisson random link-activation network with mean inter-event time of 2.0
   mean_interevent_time = 2.0
   iet = ret.exponential_distribution[ret.double](lmbda=1/mean_interevent_time)
   temporal_net = ret.random_link_activation_temporal_network(
      base_net=g, max_t=200.0,
      iet_dist=iet, res_dist=iet,
      random_state=gen)

   print(temporal_net)
   # -> <undirected_temporal_network[int64, double] with 100 verts and 20018 edges>

   # calculate reachability:
   adj = ret.temporal_adjacency.simple[temporal_net.edge_type()]()
   cluster = ret.out_cluster(
      temporal_network=temporal_net,
      temporal_adjacency=adj, vertex=0, time=0.0)

   # Total number of reachable vertices:
   print(cluster.volume())
   # -> 100

   # Is node 12 at time 100 reachable from node 0 at t=0.0?
   print(cluster.covers(vertex=12, time=100.0))
   # -> True

   # Let's see all intervals where node 15 is reachable from node 0 at t=0.0:
   print(list(cluster.interval_sets()[15]))
   # -> [(1.7428016698637445, inf)]

This can tell us that all 100 vertices are eventually reachble from vertex 0 at
time 0.0 with these configurations, and that, e.g., node 15 first becomes
reachable at time 1.742 and remains reachable after that.

For a more detailed example of temporal network reachability, check out
:doc:`this dedicated example page <examples/temporal_network>`.

Example: Static network connected component
-------------------------------------------

Let us generate :ref:`an Erdős--Rényi network <generation/gnp:Random
Erdős--Rényi network>` and find its :ref:`largest connected component
<algorithms/static_network_reachability:Undirected static networks>`:

.. code-block:: python

   import reticula as ret

   gen = ret.mersenne_twister(42)
   g = ret.random_gnp_graph[ret.int64](n=100, p=0.02, random_state=gen)

   lcc = ret.largest_connected_component(g)
   print(lcc)
   # -> <component[int64] of 93 nodes: {99, 96, ...}>

More detailed example of static network component size analysis is presented in
:doc:`its dedicated example page <examples/isotropic>`.
