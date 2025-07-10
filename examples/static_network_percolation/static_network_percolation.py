import concurrent.futures
import os
import argparse
import json

import reticula as ret
import tqdm
import numpy as np
import matplotlib.pyplot as plt


def cc_analysis(n: int, p: float, seed: int):
    # The Reticula magic is happening in this paragraph:
    state = ret.mersenne_twister(seed)
    g = ret.random_gnp_graph[ret.int64](n, p, state)
    ccs = np.array([len(cc) for cc in ret.connected_components(g)])

    largest_comp_size = np.max(ccs)
    sum_squares = np.sum(ccs**2)
    sum_cubes = np.sum(ccs**3)
    nom = sum_squares - largest_comp_size**2
    denom = n - largest_comp_size
    classic_chi = nom/denom if denom > 0 else 0.0
    expected_comp_size = sum_squares/n
    small_field = 1/n
    isotropic_chi = 1/small_field * (1/n*sum_squares - 1/(n**2)*sum_cubes)
    return largest_comp_size, classic_chi, expected_comp_size, isotropic_chi


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Analysis of connected component size and other "
        "isometric percolation properties in G(n, p) networks.")
    parser.add_argument("figure", type=str, help="output figure filename")
    parser.add_argument("output", type=str, help="output json filename")
    parser.add_argument("--size", type=int, default=10000, help="system size")
    parser.add_argument("--ens", type=int, default=100, help="ensemble size")
    parser.add_argument("-j", "--jobs", type=int, default=os.cpu_count(),
                        help="number of parallel workers")
    args = parser.parse_args()

    seeds = range(args.ens)
    size = args.size
    p_values = np.linspace(0.1/(size-1), 6/(size-1), num=200)

    largest_comps = {}
    classic_chis = {}
    expected_comps = {}
    isotropic_chis = {}
    with concurrent.futures.ThreadPoolExecutor(
            max_workers=args.jobs) as executor:
        futures = []
        for p in p_values:
            for seed in seeds:
                futures.append((p,
                                executor.submit(cc_analysis, size, p, seed)))

        for p, f in tqdm.tqdm(futures):
            largest_comp_size, classic_chi, \
                exp_comp_size, isotropic_chi = f.result()

            if p not in largest_comps:
                largest_comps[p] = []
            largest_comps[p].append(largest_comp_size)

            if p not in classic_chis:
                classic_chis[p] = []
            classic_chis[p].append(classic_chi)

            if p not in expected_comps:
                expected_comps[p] = []
            expected_comps[p].append(exp_comp_size)

            if p not in isotropic_chis:
                isotropic_chis[p] = []
            isotropic_chis[p].append(isotropic_chi)

    fig, axes = plt.subplots(2, 2, figsize=(8, 8), sharex=True,
                             gridspec_kw={"wspace": 0.3, "hspace": 0.3})

    ax_max, ax_classic_chi, ax_exp, ax_isotropic_chi = axes.flatten()

    ax_max.plot(
        p_values - 1/(size-1),
        [np.mean(largest_comps[p]) for p in p_values])
    ax_max.set_xlabel("$p - p_c$")
    ax_max.set_ylabel("Largest connected component size")

    ax_classic_chi.plot(
        p_values - 1/(size-1),
        [np.mean(classic_chis[p]) for p in p_values])
    ax_classic_chi.set_xlabel("$p - p_c$")
    ax_classic_chi.set_ylabel("Susceptibility "
                              "($\\frac{\\sum_{i>0} s_i^2}{\\sum_{i > 0} s_i}$)")

    ax_exp.plot(
        p_values - 1/(size-1),
        [np.mean(expected_comps[p]) for p in p_values])
    ax_exp.set_xlabel("$p - p_c$")
    ax_exp.set_ylabel("Expected component size")

    ax_isotropic_chi.plot(
        p_values - 1/(size-1),
        [np.mean(isotropic_chis[p]) for p in p_values])
    ax_isotropic_chi.set_xlabel("$p - p_c$")
    ax_isotropic_chi.set_ylabel("Susceptibility "
                                "($\\sum_i s_i^2 - \\frac{1}{n} \\sum_i s_i^3$)")

    fig.savefig(args.figure)

    report = {
        "size": size,
        "p_values": list(p_values),
        "largest_component_size":
            [np.mean(largest_comps[p]) for p in p_values],
        "old_school_susceptibility":
            [np.mean(classic_chis[p]) for p in p_values],
        "expected_component_size":
            [np.mean(expected_comps[p]) for p in p_values],
        "susceptibility":
            [np.mean(isotropic_chis[p]) for p in p_values]}

    with open(args.output, 'w') as out:
        json.dump(report, out)
