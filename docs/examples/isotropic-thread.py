import numpy as np
import reticula as ret
import matplotlib.pyplot as plt

from concurrent.futures import ThreadPoolExecutor
from functools import partial

def lcc_size(n, p):
    state = ret.mersenne_twister()
    g = ret.random_gnp_graph[ret.int64](n, p, state)
    return len(ret.largest_connected_component(g))

n = 1000000
ps = np.linspace(0, 2./n)

with ThreadPoolExecutor(max_workers=8) as e:
    lccs = e.map(partial(lcc_size, n), ps)

plt.plot(ps, list(lccs))
plt.show()
