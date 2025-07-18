Exploring temporal (hyper)networks
==================================

Temporal networks contain events that happen at specific times.  We
construct one from a static base network and briefly look at simple
reachability queries.  Install the library with ``pip install
reticula`` and import it::

   >>> import reticula as ret

Random link activation
----------------------

Here we use a random 4-regular graph as the base structure and activate
its links according to an exponential inter-event time distribution::

   >>> gen = ret.mersenne_twister(42)
   >>> base = ret.random_regular_graph[ret.int64](
   ...     size=64, degree=4, random_state=gen)
   >>> iet = ret.exponential_distribution[ret.double](lmbda=1.0)
   >>> temporal = ret.random_link_activation_temporal_network(
   ...     base_net=base, max_t=32, iet_dist=iet, res_dist=iet,
   ...     random_state=gen)
   >>> temporal
   <undirected_temporal_network[int64, double] with 64 verts and 4026 edges>

Temporal hypergraphs
--------------------

Using a hypergraph base works just the same.  Only the edge type
changes::

   >>> gen = ret.mersenne_twister(42)
   >>> hbase = ret.random_uniform_hypergraph[ret.int64](
   ...     size=100, edge_degree=3, edge_prob=0.01, random_state=gen)
   >>> iet = ret.exponential_distribution[ret.double](lmbda=1.0)
   >>> hyper_temporal = ret.random_link_activation_temporal_network(
   ...     base_net=hbase, max_t=16, iet_dist=iet, res_dist=iet,
   ...     random_state=gen)
   >>> hyper_temporal
   <undirected_temporal_hypernetwork[int64, double] with 100 verts and 26675 edges>
   >>> hyper_temporal.edge_type()
   <class 'undirected_temporal_hyperedge[int64, double]'>

Basic reachability
------------------

Simple spreading corresponds to the default temporal adjacency.  The
cluster of events reachable from node ``0`` at time ``0`` is obtained
with :py:func:`out_cluster`::

   >>> adj = ret.temporal_adjacency.simple[temporal.edge_type()]()
   >>> cluster = ret.out_cluster(temporal_network=temporal,
   ...     temporal_adjacency=adj, vertex=0, time=0.0)
   >>> cluster.volume()
   64
   >>> cluster.mass()
   inf
   >>> cluster.lifetime()
   (0.0, inf)
   >>> cluster.covers(vertex=12, time=0.1)
   False
   >>> cluster.covers(vertex=12, time=3.1)
   True

You can directly inspect the intervals where a vertex is reachable from the
source of the sprading cluster::

   >>> int_set = cluster.interval_sets()[12]
   >>> int_set
   <interval_set[double] from t=2.394805838263237 to t=inf>
   >>> list(int_set)  # set of all "infected" time periods for vertex 12
   [(2.394805838263237, inf)]

The same reachability functions work on this temporal hypergraph as well. For a
more complex example, see the :ref:`temporal network reachability
<examples/temporal_network:Spreading and reachability in temporal networks>`
example.
