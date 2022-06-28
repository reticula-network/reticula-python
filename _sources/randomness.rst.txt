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
number generator <https://github.com/imneme/pcg-cpp/>_`.

On Python side, everything is slightly more involved. You cannot simply use the
random number generators implemented by Python or NumPy, as Reticula cannot
manipulate Python objects in any way that matters. Similar situation is also in
place for distributions. We have provided bindings to some pseudorandom number
generators and distributions for use with this library, some bindings over C++
standard library implementation (e.g., :py:class:`geomtric_distribution` and
:py:class:`exponential_distirbution`) and some based on our own implementation.

.. warning::
   Reticula currently relies on C++ standard library distributions and
   pseudorandom number generators, execept for a few distributions that are
   implemented by Reticula. This has negative implecations for reproducability
   across platforms. At some point in the future, these will have to change into
   ones with reproducability guarantees tied to Reticula version and not the
   platform or the standard library implementation. Until this change happens,
   we will try our best keep the Python build environment consistant, but there
   are no guarantees.

For now, the only real thing you can do with these classes are to create them
and pass them on to Reticula functions, as Reticula is not a general purpose
numerical computation library.

Pseudorandom number generators
------------------------------

.. py:class:: mersenne_twister([seed: int])

   Creates an instance of 64-bit Mersenne twister :cite:p:`nishimura2000tables`.
   Bindings over C++ standard library implementation.

   We recommand using one pseudorandom number generator per thread in
   multi-threaded environment.

   If no :py:`seed` is provided, the generator is seeded using a
   non-deterministic source, e.g., a hardware device, if one is available.


Distributions
-------------

.. py:class:: geometric_distribution[integral_type](p: float)

   A discrete distribution of the number of required Bernoulli trials with
   probability :py:`p` to get one success. This distribution has a mean of
   :math:`\frac{1}{p}`. It's the discrete analogue to
   :py:class:`exponential_distribution[floating_point_type]`

.. py:class:: exponential_distribution[floating_point_type](lambda: float)

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
   :py:class:`power_law_with_specified_mean[floating_point_type]`.

.. py:class:: hawkes_univariate_exponential[floating_point_type](\
   mu: float, alpha: float, theta: float, phi: float = 0.0)

   A univariate exponential formulation of Hawkes self-exciting process. The
   parameter :py:`mu` indicates background (or exogenous) intensity of events,
   indicating the random probability of events happening without being caused
   through self-excitement, parameter :py:`alpha` indicates the infectivity
   factor, often interpreted as the expected number of induced self-exciting
   events per each event, :py:`theta` indicates the rate parameter of the delay
   and :py:`phi` specifies the history of the distribution until this point in
   time.

.. py:class:: delta_distribution[numeric_type](mean: int | float)

   Always returns the value of :py:`mean`.
