Isotropic bond-percolation in G(n, p) networks
==============================================

The goal of this example is to visualise what happens to the largest component
size when you randomly remove edges from a :ref:`random G(n, p) network
<generation/gnp:Random Erdős--Rényi network>`:

.. literalinclude:: isotropic.py
   :language: python
   :linenos:

Here is a more sophisticated version of this example that uses the
multi-threading capabilities of Reticula to utilise more CPU cores:

.. literalinclude:: isotropic-thread.py
   :diff: isotropic.py
   :language: python
   :linenos:
