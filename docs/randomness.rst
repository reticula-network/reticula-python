Randomness
==========

Simulating physical systems with computers often involve generating random
numbers or randomly sampling from a set. This poses a challenge to programmers,
in that computers, as mostly deterministic creatures, are quite bad at this sort
of task.

Another aspect of this problem is reproducibility. Researchers need their
results to be reproducible, meaning that if someone else runs the same
code on another computer, they should be able to get the same results as
everyone else. True random number generators are not really the tool for this
purpose.

Pseudorandom number generators, on the other hand, can produce results "random
enough" for the purpose of scientific simulation. On C++ side, you can simply
use any pseudorandom number generator as long as it conforms to the concept
:cpp:`std::uniform_random_bit_generator`, for example, Mersenne Twister
implementation from the standard library :cpp:`std::mt19937_64` or `PCG random
number generator <https://github.com/imneme/pcg-cpp/>`_.

On Python side, everything is slightly more involved. You cannot simply use the
random number generators implemented by Python or NumPy, as Reticula cannot
manipulate Python objects in any way that matters. Similar situation is also in
place for distributions. We have provided bindings to some pseudorandom number
generators and distributions for use with this library, some bindings over C++
standard library implementation (e.g., :py:class:`geometric_distribution` and
:py:class:`exponential_distribution`) and some based on our own implementation.


.. admonition:: Example: Working with random numbers
   :class: tip

   While the main use-case for bit generators and distributions is to be passed
   to other Reticula methods, you can also use them directly as callable
   objects. For example, to generate random samples from the exponential
   distribution, you can use the following code:

   .. code-block:: pycon

      >>> import reticula as ret
      >>> gen = ret.mersenne_twister(42)  # seed the generator
      >>> gen()  # Returns a random 64-bit integer
      13930160852258120406
      >>> dist = ret.exponential_distribution[ret.double](lmbda=2.0)
      >>> dist(gen)  # Random sample from the exponential distribution
      0.5094821440086138
      >>> dist(gen)
      0.6974560955843683

   Use random bit generators, e.g., :py:class:`mersenne_twister` as a source of
   randomness for other distributions. Use the same pattern to generate random
   samples from other distributions.

.. warning::

   Reticula currently relies on C++ standard library distributions and
   pseudorandom number generators, execept for a few distributions that are
   implemented by Reticula. This has negative implecations for reproducability
   across platforms. At some point in the future, these will have to change
   into ones with reproducability guarantees tied to Reticula version and not
   the platform or the standard library implementation. Until this change
   happens, we will try our best keep the Python build environment consistant,
   but there are no guarantees.

Pseudorandom bit generators
---------------------------

The pseudorandom bit generators can be initialised using an integer seed. If no
seed is provided, the generator is seeded using a non-deterministic source,
e.g., a hardware device, if one is available. If no non-deterministic source is
available, it might rely on an implementation defined deterministic source.

.. warning::

   The default initialisation behaviour of random bit generator are completely
   different in C++ and Python. In Python, default initialisation, e.g.,
   :py:`ret.mersenne_twister()` generates a random state seeded with a
   non-deterministic source like ``/dev/urandom`` on Linux. In C++, default
   initialisation of bit generators is equivalent to using a constant seed.


You can use the :py:`__call__` method to get raw values, e.g.:

.. code-block:: pycon

   >>> gen = ret.mersenne_twister(42)
   >>> gen()
   13930160852258120406
   >>> gen()
   11788048577503494824
   >>> gen()
   13874630024467741450


.. py:class:: mersenne_twister([seed: int])

   Creates an instance of 64-bit Mersenne twister
   :cite:p:`nishimura2000tables`. Bindings over C++ standard library
   implementation.

   We recommand using one pseudorandom bit generator per thread in
   multi-threaded environment.

   .. py:method:: __call__() -> int

      Advances the internal state and returns the generated value.


Distributions and stochastic generators
---------------------------------------

.. py:class:: geometric_distribution[integral_type](p: float)

   A discrete distribution of the number of required Bernoulli trials with
   probability :py:`p` to get one success. This distribution has a mean of
   :math:`\frac{1}{p}`. It's the discrete analogue to
   :py:class:`exponential_distribution`

.. py:class:: exponential_distribution[floating_point_type](lmbda: float)

   A continuous distribution indicating the time between two consecutive events
   if that event happens at a constant rate, i.e., a Poisson point process. The
   parameter :py:`lambda` indicates the rate and the distribution has a mean of
   :math:`\frac{1}{\lambda}`.

.. py:class:: power_law_with_specified_mean[floating_point_type](\
   exponent: float, mean: float)

   A power-law distribution with minimum-value cutoff, selected in a way to
   produce values with mean :py:`mean`. The parameter :py:`exponent`, indicating
   the power-law exponent has to be larger than 2.

.. py:class:: residual_power_law_with_specified_mean[floating_point_type](\
   exponent: float, mean: float)

   Residual distribution of the distribution
   :py:class:`power_law_with_specified_mean`.

.. py:class:: hawkes_univariate_exponential[floating_point_type](\
   mu: float, alpha: float, theta: float, phi: float = 0.0)

   A univariate exponential formulation of Hawkes self-exciting process. The
   parameter :py:`mu` indicates background (or exogenous) intensity of events,
   indicating the random probability of events happening without being caused
   through self-excitement, parameter :py:`alpha` indicates the infectivity
   factor, often interpreted as the expected number of induced self-exciting
   events per each event, :py:`theta` indicates the rate parameter of the delay
   and :py:`phi` specifies the history of the generator until this point in
   time.

.. py:class:: uniform_real_distribution[floating_point_type](a: float, b: float)

   Returns floating point value selected uniformly at random from the range
   :math:`[a, b)`.

.. py:class:: uniform_int_distribution[integral_type](a: int, b: int)

   Returns an integer value selected uniformly at random from the range
   :math:`[a, b]`.

.. py:class:: delta_distribution[numeric_type](mean: int | float)

   Always returns the value of :py:`mean`.
