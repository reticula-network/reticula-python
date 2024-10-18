Spreading and reachability in temporal networks
===============================================

In this example, we construct a random link-activation temporal network, then
compare various reachability statistics for different types of temporal
adjacency.

Let's say you want to study the spreading of a disease or some other effect on
a temporal network. There are many different models, ranging from very simple
to very intricate and specialised, that might be relavant for this use.

Making the network
------------------

Let's start first by creating a random temporal network. In this case we
generate a random temporal network where the nodes have an underlying random
:math:`k`-regular structure, using :py:func:`random_regular_graph`, with each
link gets activated with an exponential inter-event time distribution. In other
words, in our "friendship" network, each "person" is friends with exactly
:math:`k` other randomly selected people, and the time between consecutive
meeting of each two friends are drawn from an exponential distribution with a
given mean, i.e. meetings are a Poisson process.

.. code-block:: python

   import reticula as ret

   max_t = 64
   size = 128
   k = 4
   mean_iet = 1.0

   gen = ret.mersenne_twister()
   g = ret.random_regular_graph[ret.int64](size=size, degree=k, random_state=gen)

   iet = ret.exponential_distribution[ret.double](lmbda=1/mean_iet)
   residual_iet = iet

   temporal_net = ret.random_link_activation_temporal_network(
      base_net=g,
      max_t=max_t,
      iet_dist=iet,
      res_dist=residual_iet,
      random_state=gen)

The function :py:func:`random_link_activation_temporal_network` takes a static
base network :py:`base_net`, a maximum simulated time :py:`max_t`, an
inter-event time distribution :py:`iet_dist`, a residual time distribution
:py:`res_dist` and a pseudo-random number generator to generate a random
link-activation network from :math:`t = 0` to :math:`t = t_\text{max}`.

The `residual time`_ distribution generates the distribution of time to the
next event, starting at a random time, i.e. if you arrive at a bus stop at a
random time, how long do you have to wait for a bus to arrive if busses arrive
at intervals drawn from the inter-event time. For the case of Poisson process,
this happens to be the same distribution as the waiting times.

Our temporal network is now an undirected temporal network with 128 vertices
and around 16 thousand events.

.. code-block:: pycon

   >>> temporal_net
   <undirected_temporal_network[int64, double] with 128 verts and 16157 edges>

.. _`residual time`: https://en.wikipedia.org/wiki/Residual_time


Simple spreading process
------------------------

Next, we calculate the charactristic quantities of the most simple spreading
process model. In this model, once an effects, e.g., a disease or information,
reaches a node, that node will forever remain "infectious", spreading that
effect to anyone else they come in contact with. This is more or less
equivalent to the Susceptible--Infected (SI) model of epidemic spreading.

In temporal network words, many of these different types of spreading processes
can be understood in terms of :ref:`temporal adjacency
<algorithms/temporal_network_reachability:temporal adjacency>`. Imagine two
events :math:`e_1` and :math:`e_2`. If the first one carries a disease, what
are the conditions for the second one to carry the disease as well as a
consequence of the first event transmitting the disease? For the simple case of
simple adjacency on undirected networks, the only condition for the adjacency
of these two events is that they share at lease one vertex in common, and that
:math:`e_2` happens after :math:`e_1`. This gets more and more involved for,
e.g., directed temporal networks or temporal networks where events take some
time from start to finish, but here we only care about the simple definition.

Single-source simulation
^^^^^^^^^^^^^^^^^^^^^^^^

Let's now see what would be the result of a spreading process originating from
a specific node at a certain time, using this simple adjacency rules. This can
be accomplished using :py:func:`out_cluster`:

.. code-block:: python

   adj = ret.temporal_adjacency.simple[temporal_net.edge_type()]()
   cluster = ret.out_cluster(
       temporal_network=temporal_net,
       temporal_adjacency=adj,
       vertex=0, time=0.0)

The cluster object, an instance of :py:class:`temporal_cluster`, now contains
information about the entire spreading cluster starting from vertex 0 at time
0.0, including who got infected when. We can see for example that every node
got infected at one point or another:

.. code-block:: pycon

   >>> cluster.volume()
   128

We can also see all the intervals when a certain vertex (for example node 5)
has been infected:

.. code-block:: pycon

   >>> int_set = cluster.interval_sets()[5]
   >>> int_set
   <interval_set[double] from t=2.7580437394574595 to t=inf>
   >>> list(int_set)
   [(2.7580437394574595, inf)]

Also, it is possible to see how many events (and exactly which ones)
participated in the spreading process and whether a specific vertex at a
specific time.

.. code-block:: pycon

   >>> len(cluster)
   16114
   >>> list(cluster)
   [undirected_temporal_edge[int64, double](69, 84, time=59.1906391191876), undirected_temporal_edge[int64, double](20, 126, time=16.842526559964774), undirected_temporal_edge[int64, double](16, 107, time=4.880354855014931), ....]
   >>> cluster.covers(12, 1)
   False


This is telling us that node 5 first got infected at time :math:`t = 2.7` and
remained infected forever.


Multi-source simulation
^^^^^^^^^^^^^^^^^^^^^^^

:py:func:`out_cluster` provides a powerful tool, but sometimes, you need to
know the range of possible outcomes from different starting points. Of course
one approach is to use :py:func:`out_cluster` multiple times with different
starting vertices and times. This, however, is not necessarily the most
efficient approach, as it requires looping over every event in the temporal
network for each call of the function.

We can calculate the out-cluster from all possible starting points with a
single backwards scan of the network, using the method presented in
:cite:t:`badie2020efficient`, using the :py:func:`out_clusters` method (note
the plural "clusters").

.. code-block:: python

   clusters = ret.out_clusters(
       temporal_network=temporal_net, temporal_adjacency=adj)

The variable :py:`clusters` now contains a list tuples of all events on the
temporal network, paired with the cluster of spreading that would result if a
spreading process starts right before the time of that event.

This on its own, however, requires sacrificing a lot of memory. Even for a
small temporal network like this, you might need around to 7.7GB of RAM and it
takes around 20 seconds to run on a modern CPU core. This is due to the fact
that at every stage of the algorithm we have to keep exact track of membership
of every node in every cluster. Turns out, however that in many cases we don't
actually need this information in the final results, as we mostly only care
about the various statistics of a cluster such as number of unique nodes, total
lifetime of the spreading process or total "human-hours" of infection.

In cases like this, we can use :py:func:`out_cluster_sizes`, which throws out
the actual cluster memberships when they become irrelevant to the algorithm,
only keeping the afformentioned charactristic quantities, namely mass, volume
and lifetime for each possible source.

.. code-block:: python

   clusters = ret.out_clusters(
       temporal_network=temporal_net, temporal_adjacency=adj)

This already drops the peak memory requirement by a factor of 50! The resulting
charactristic quantities are exact, but there is not much detail left in each
cluster, which are instances of :py:class:`temporal_cluster_size`. You are
still able to get exact value for mass, volume and lifetime and check exactly
how many events participated in each spreading cluster, but you can't get a
list of those events.

Multi-source estimation
^^^^^^^^^^^^^^^^^^^^^^^

The :py:func:`out_cluster_sizes` method still keeps exact track of every event
involved in every spreading process, even if it throws out that list as soon as
it can in the course of the traversal of the temporal network.

We can get results much faster and a whole lot lighter (in terms of memory use)
if instead of keeping accurate track every event involved in each spreading
cluster, we use probabilistic counting methods to keep track of these
charactristic quantities.

:py:func:`out_cluster_size_estimates` method does exactly that. It uses the
full force of the approach described in :cite:t:`badie2020efficient` to get
estimated values for mass, volume and number of events participating in each
spreading cluster.

.. code-block:: python

   clusters = ret.out_cluster_size_estimates(
       temporal_network=temporal_net, temporal_adjacency=adj,
       time_resolution=0.1, seed=0)

This results in a runtime of ~0.8 seconds, and memory usage low enough that
becomes hard to measure in this scale (< 10MB). The downside is that mass,
volume and number of events are now only accurate to ±1.1% of their exact
value.

The volume and event count work by directly employing a HyperLogLog++
probabilistic cardinality estimator\ :cite:p:`heule2013hyperloglog`. The mass
is calculated by dividing the timeline of each node to steps of size
:py:`time_resolution`, then counting unique combinations of vertex name and
time step that is in the spreading cluster using the probabilistic cardinality
estimator. The lifetime of the cluster is still measured exactly.

The seed parameter controls the seed used for hashing in the HyperLogLog++
cardinality estimators. By running the function multiple times with different
seeds and averaging the results, you can obtain accuracies higher than the
default ±1.1%.

These sacrifices are made so that each cluster "sketch" stays within a constant
memory footprint, as opposed to normal cluster objects that grow over time.

Other types of spreading processes
----------------------------------

So far we only used the most simple adjacency type, corresponding to a simple
Susceptible--Infected (SI) process, but this might not be the most suitable
model real-world phenomena. Specifically, processes where the effect only
lingers in each node for a finite amount of time. In this section we will talk
about other, slightly more realistic models of reachability and spreading
processes.


Limited waiting time
^^^^^^^^^^^^^^^^^^^^
For example, let's say you are interested in reachability in a public
transportation network. You can model each bus stop and train station as
vertices in a temporal network, and each bus or train trip between consecutive
stations as a link. In this scenario, the set of all vertices and times that
can be reached from a starting vertex and time for the out-cluster of that
starting point and time. To put it in other words, if vertex :math:`v` at time
:math:`t` is in the out-cluster of :math:`v_0` at :math:`t_0`, then there is at
least one valid time-respecting path between the two.

It is, however, not very likely that a traveller would stay in a station
waiting for a bus or a train to arrive for an indefinite amount of time. Let's
say we limit valid time-repsecting paths to those with a miximum waiting time
of :math:`\delta t`.

This limited waiting-time reachability can be expressed in terms of temporal
adjacency of two events. The two events :math:`e_1` and :math:`e_2` are
adjacent with a maximum waiting time :math:`\delta t` if they are adjacent
(i.e., if :math:`e_2` starts after the end of :math:`e_1` and they share at
least one vertex in common) and the start time of :math:`e_2` is at most
:math:`\delta t` away from the end of :math:`e_1`.

.. code-block:: python

   lwt_adj = ret.temporal_adjacency.limited_waiting_time[temporal_net.edge_type()](dt=3.0)
   cluster = ret.out_cluster(
       temporal_network=temporal_net,
       temporal_adjacency=lwt_adj,
       vertex=0, time=0.0)

This creates an adjacency object with a maximum waiting time of 3.0 units of
time. You can use the other cluster functions the same way as before, simply by
using the new adjacency object as a parameter.

Of course, the public transportation example from above differs from the
previous examples, in that the underlying temporal network is both directed and
delayed, meaning that a trip between two stations only move people in one
direction and that it takes some time to move from one stop to the next and the
execution of the event is not instantainious. A better temporal network type
for representing transport networks is
:py:class:`directed_delayed_temporal_network`, where each event has two
distinct timestamps instead of one:

.. code-block:: python

   e = ret.directed_delayed_temporal_edge[ret.int64, ret.double](
      tail=1, head=2, cause_time=2.0, effect_time=3.0)

The example above shows a :py:class:`directed_delayed_temporal_edge` going from
node 1 to node 2, where the "departure time" is 2.0 and the "arrival time" is
3.0.

Exponential/geometric waiting time
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In other real-world phenomena, the idea of a limit for waiting time for valid
time-respecting paths makes sense, but perhaps not a constanc cutoff described
by a single value. For example, let's say you are modelling infromation
spreading, e.g., sprading of gossip, where each person hearing a gossip has a
constant probability of forgetting it at every unit of time. This means that
the maximum waiting times are drawn from an exponential distribution.


.. code-block:: python

   mean_cutoff_time = 2.0
   exp_adj = ret.temporal_adjacency.exponential[temporal_net.edge_type()](
       rate=1/mean_cutoff_time, seed=42)
   cluster = ret.out_cluster(
       temporal_network=temporal_net,
       temporal_adjacency=exp_adj,
       vertex=0, time=0.0)

The seed parameter here controls the generation of waiting times. This will
create a single realisation of the spreading process. To get a more accurate
range of possible outcomes, re-run this functions with different seed values.

Note that the exponential adjacency only works for networks with continues time
(i.e., :py:class:`double` time type). For discrete time types (
:py:class:`int64`) you need to use the geometric adjacency
:py:class:`temporal_adjacency.geometric` which has the maximum waiting times
drawn from the geometric distribution.

Infectious and non-infectious events
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Simply assuming every event will cause a transmission event might not be very
realistic. Spreading processes on temporal networks sometimes assume an
infection probability :math:`p`, similar to the role of infectious rate
:math:`\beta` in SIS processes, that determines wheter a particular event can
carry a disease or not. In Reticula, we can do this by creating a new temporal
network where each event is occupied (kept) independently with probability
:math:`p`:

.. code-block:: python

   p = 0.8
   new_net = ret.uniformly_occupy_edges(temporal_net, occupation_prob=p, random_state=gen)

We can then run the same processes on the new_net instead of the old one.

Limited waiting time processes and SIS models
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
With a little bit of work, you can see how SI processes with an infection
probability 1.0 on temporal network are isomorphic to reachability. While the
relationshio between SI model and simple adjacency is easy to understand, the
relationship between exponential waiting time adjacency and SIS processes are
more nuanced. In exponential limited waiting-time adjacency, similar to the the
usual formulation of the SIS process, each node stays infected and contagious
for a length of time drawn from an exponential distribution with a given mean.
The difference arrises when thinking of how "re-infections" affect this
process. This is however, a topic very involved topic, perhaps enough for a
research paper or maybe several.
