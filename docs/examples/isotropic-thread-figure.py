from concurrent.futures import ThreadPoolExecutor
from functools import partial

import numpy as np
import reticula as ret
import matplotlib.pyplot as plt
from tqdm import tqdm


def lcc_size(n, p):
    state = ret.mersenne_twister()
    g = ret.random_gnp_graph[ret.int64](n, p, state)
    return len(ret.largest_connected_component(g))


n = 1000000
ps = np.linspace(0, 2./n, num=100)

with ThreadPoolExecutor(max_workers=16) as e:
    lccs = list(tqdm(e.map(partial(lcc_size, n), ps),
                     total=len(ps)))

fig, ax = plt.subplots(figsize=(6, 4))
ax.plot(ps, lccs)
ax.ticklabel_format(useMathText=True)

ax.set_xlabel("Edge probability $p$")
ax.set_ylabel("Largest connected component size")

fig.tight_layout()
fig.savefig("isotropic.pdf")
fig.savefig("isotropic.svg")
