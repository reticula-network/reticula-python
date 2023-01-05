import numpy as np
import reticula as ret
import matplotlib.pyplot as plt

def lcc_size(n, p):
    state = ret.mersenne_twister()
    g = ret.random_gnp_graph[ret.int64](n, p, state)
    return len(ret.largest_connected_component(g))

n = 1000000
ps = np.linspace(0, 2./n)

lccs = [lcc_size(n, p) for p in ps]

plt.plot(ps, list(lccs))
plt.show()
