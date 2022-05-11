Quick Start
===========

For Python developers
---------------------

The very first step is to find a suitable development environment. Reticula is
currently compatible with Linux systems based on GNU C Library 2.17 or higher,
which at the moment means practically any distribution released in the past 6
years except for Alpine Linux. If you have no preferences on the subject, we
recommend a long-term support (LTS) version of Ubuntu, such as 22.04.


Setting up the environment
^^^^^^^^^^^^^^^^^^^^^^^^^^

In this section, we will explore the most basic form of installation of
Reticula. Unfortunately, the current state of Python development environment is
`not as intuitive as it can be <https://xkcd.com/1987/>`_, so if you are working
on a computer that is administered by someone else, such a University
workstation or laptop, ask your system administrators what is the best way to
install a package for your specific setup.

First, open the terminal and check if you have the proper Python version
installed:

.. code-block:: console

   $ python --version
   Python 3.8.10

Acceptable values are, at the moment, 3.8, 3.9 or 3.10, though there is
experimental support for PyPy 3.8 and 3.9 as well. If your Python version is
not in this range, you can install proper Python version using the tools
provided by your operating system.

.. note::
   In Ubuntu and other Debian based Linux distributions, by default all Python
   binaries are versioned, meaning that you should be replacing all instances
   of :code:`python` in the command line with :code:`python3`.

Next, let's make sure you have the most recent version of pip, the standard
Python package-management system:

.. code-block:: console

   $ python -m pip install --upgrade pip

Finally, to install the Reticula package

.. code-block:: console

   $ python -m pip install reticula

If this command succeeds, you should be ready to go! Let's check if everything
is ready by running a one-liner script that only tries to import Reticula:

.. code-block:: console

   $ python -c "import reticula" && echo "success\!"
   success!

Getting started with Reticula
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

First, let's open a Python console, also called a REPL:

.. code-block:: console

   $ python
   Python 3.8.10 (default, Jun  4 2021, 15:09:15)
   >>>

You can now enter Python commands one by one and have the results shown to you
immediately. This is useful for testing and learning. Let's import Reticula and
try to create a network:

.. code-block:: pycon

   >>> import reticula as ret
   >>> g = ret.regular_ring_lattice[ret.int64](size=100, degree=4)
   >>> g
   <undirected_network[int64] with 100 verts and 200 edges>

Let's try to dissect these commands. First, we imported Reticula but instructed
python to use the alias :py:`ret` to refer to it. This can help you avoid having
to type :py:`reticula` over and over again.

Second, we called the function :py:`regular_ring_lattice[ret.int64]`. This
syntax might look a bit weird or unnatural to people coming from a dynamic
typing background. Remember that Reticula in Python is a thin shell over C++, so
some functions need more information about what type of network or edges you
want to construct, especially where this is not deducible from the things you
passed in as arguments. This is refelcted in the type of the output network
:py:`g`, which is a :py:`ret.undirected_network[ret.int64]`, i.e., an undirected
dyadic static network with 64-bit signed integers as vertices.

Here, we instructed Reticula to construct a 4-regular ring lattice with 100
vertices, where each vertex is a 64-bit signed integer. You can compare this,
for example, to the :py:`dtype` parameter that many NumPy functions expect:

.. code-block:: python

   import numpy as np
   np.array([1, 2, 3, 4], dtype=np.int64)

Let's get back to Reticula. We can inspect the network :py:`g`. Let's have a
look at the edges and vertices of :py:`g`:

.. code-block:: pycon

   >>> g.edges()
   [undirected_edge[int64](0, 1), undirected_edge[int64](0, 2),
   undirected_edge[int64](0, 98), ..., undirected_edge[int64](98, 99)]
   >>> g.vertices()
   [0, 1, 2, 3, 4, 5, 6, 7, ... , 99]

So, the edges of network :py:`g` are also carrying the same type information as
the network itself. Let's get one of the edges and inspect that:

.. code-block:: pycon

   >>> e = list(g.edges())[0]
   >>> e
   undirected_edge[int64](0, 1)
   >>> e.incident_verts()
   [0, 1]
   >>> e.vertex_type() == ret.int64
   True


Generating random networks
^^^^^^^^^^^^^^^^^^^^^^^^^^

Let's try using more interesting network models. Random network models, such as
Erdős--Rényi model, depend on random number generators to work. Moreover,
Reticula cannot safely manipulate Python objects, such as the Python standard
library pseudo-random number generator :py:`random.Random`, while retaining the
ability to do parallel work in different threads. Reticula, therefore, provides
bindings for a pseudo-random number generator that can safely be used
internally.

.. code-block:: pycon

   >>> state = ret.mersenne_twister(seed=42)

The variable state now holds a pseudo-random number generator created with seed
value 42. Any Reticula algorithm, when passed this state, should produce the
same outcome as long as the same seed is used.

.. code-block:: pycon

   >>> state = ret.mersenne_twister(seed=42)
   >>> ret.random_gnp_graph[ret.int64](n=1000, p=0.05, random_state=state)
   <undirected_network[int64] with 1000 verts and 25091 edges>

   >>> # on some other computer:
   >>> state = ret.mersenne_twister(seed=42)
   >>> ret.random_gnp_graph[ret.int64](n=1000, p=0.05, random_state=state)
   <undirected_network[int64] with 1000 verts and 25091 edges>

Usually, you need to make a single pseudo-random number generator for your
python script, or one per thread for multi-threaded scripts since the order of
execution is not clear. The seed(s) for the random number generators can be one
of the inputs to your script, making it much easier for you and other to
reproduce your results.

Using the algorithms
^^^^^^^^^^^^^^^^^^^^

Let's now use some of the algorithms. Let's generate a thinner network and study
connectivity in this static network:

.. code-block:: pycon

   >>> state = ret.mersenne_twister(seed=42)
   >>> g = ret.random_gnp_graph[ret.int64](n=1000, p=0.005, random_state=state)
   >>> comps = ret.connected_components(g)
   >>> len(comps)
   8

So this random network consists of 8 connected components. Let's see how the
component sizes are distributed, then get the largest component:

.. code-block:: pycon

   >>> ret.is_connected(g)
   False
   >>> [len(c) for c in comps]
   [1, 1, 1, 1, 1, 1, 1, 993]
   >>> lcc = max(comps, key=len)
   >>> lcc
   <component[int64] of 993 nodes: {999, 998, 997, 996, 995, 994, 993, 992,
   991, 990, ...})>

So a component, which is just a set of vertices, also carries the same type
information as all other types. We can inspect the membership in a component and
turn it into a plain old Python list of numbers:

.. code-block:: pycon

   >>> 10 in lcc
   True
   >>> 59 in lcc
   False
   >>> [v for v in g.vertices() if v not in lcc]
   [59, 98, 260, 669, 713, 874, 937]

Let's now get the subgraph of :py:`g` induced by the largest connected
components:

.. code-block:: ptcon

   >>> g2 = ret.vertex_induced_subgraph(g, lcc)
   >>> g2
   <undirected_network[int64] with 993 verts and 2498 edges>
   >>> ret.is_connected(g2)
   True

We can also check out some other properties of the network, such as its density
or average degree:

.. code-block:: ptcon

   >>> # Average degree:
   >>> sum(g.degree(v) for v in g.vertices())/len(g.vertices())
   4.996
   >>> ret.density(g)
   0.005001001001001001
   >>> ret.is_reachable(g, 1, 3)
   True
   >>> ret.is_reachable(g, 1, 59)
   False
