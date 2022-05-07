# Random network percolation

In this example, we study the connectivity phase transition in
[random `G(n, p)` networks][gnp] as controlled by parameter `p`. We are
interested in the evolution of expected and largest connected component size.
Also, we will study two different "susceptibility" measures, one based on small
component size distribution, called `classic_chi` in the code, and one based on
expected change in the expected component size after inducing a miniscule
external field, called `isotropoc_chi`.

The code tries to utilise all cores on your computer without using separate
Python processes. Remember that while almost all the computations that run
inside Reticulum library functions can be parallelised, the more Python
functions we run in the `cc_analysis` function, which is the multi-threaded part
of your code, [the lower your overall speedup is going to be][amdahl]. In this
example, the networks with a lower `p` values spend less calculation time in the
Reticulum library (i.e. the functions `reticulum.random_gnp_graph` and
`reticulum.connected_components` run faster for less dense network) but slightly
more time in the Python functions since larger number of components means more
calculation time for list comprehensions.

[gnp]: https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model
[amdahl]: https://en.wikipedia.org/wiki/Amdahl%27s_law

## Running the example

Run this example for 100 random networks of size 10000 nodes:
```
$ time python examples/static_network_percolation/static_network_percolation.py --size 10000 --ens 100 /tmp/figure.svg /tmp/report.json
100%|█████████████████████████████████████████████████████████████| 20000/20000 [01:48<00:00, 183.95it/s]

real    2m11.495s
user    9m15.110s
sys     0m2.580s
```

Note the difference between user+sys times and the real "clock" time. This
signifies a speedup of around 4.2 times, achieved on an 4-core Intel Core
i7-6700HQ laptop CPU supporting a total of 8 SMT threads.

The output figure should look something like this:
![4 plot showing changes in compoent size and susceptibility][fig]

[fig]: https://raw.githubusercontent.com/reticulum-network/reticulum-python/main/examples/static_network_percolation/figure.svg
