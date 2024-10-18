Isotropic bond-percolation in G(n, p) networks
==============================================

The goal of this example is to visualise what happens to the largest component
size when you randomly occupying edges in a static, undirected network.

A :ref:`random G(n, p) network <generation/gnp:Random Erdős--Rényi network>` can
generates a random network with each edge occupied with probability :math:`p`.
So the exercise boils down to generating :math:`G(n, p)` networks with various
values of :math:`p` and plotting the largest component sizes.

.. literalinclude:: isotropic.py
   :language: python
   :linenos:

This, after doing a lot of processing, produces a figure that looks like this,
minus the axis labels and other niceties:

.. image:: isotropic.svg
   :width: 600
   :alt: A line plot with x axis between 0 to 2e-6 labelled "edge probability
         p", and the y axis ranging from 0 to 800000 labelled "largest connected
         component size". The y values of the line are close to zero from x=0 to
         x=1e-6, then they suddenly start increasing.


While this script definitly works, it is only utilising one CPU core. We can use
more CPU cores (and run the code faster) using multi-processing. This, however,
would be wasteful, as it entails running multiple independent python processes,
each loading the standard library and Reticula in mostly separate places in the
memory. The separate processes also have to communicate with each other by
pickling and unpickling Python objects, which can be inefficient.

More desirable would be to perform this in multi-threaded setting. This reduces
the memory-use overhead significantly, and mitigates the inter-process
communication issue mentioned above as threads can access shared memory. In
general, this also increases the risk of race conditions. On Reticula, network
and edge types are immutable, so the risk race conditions when sharing a network
object across threads is minimised.

In this case, there is no need to share anything other than the parameter
:math:`p` across threads. In the next example, we run the function
:py:`lcc_size` on 8 threads. Note that each thread creates its own instance of
pseudorandom number generator using the command
:py:`state = ret.mersenne_twister()`.

.. literalinclude:: isotropic-thread.py
   :language: python
   :linenos:
