import math
import statistics

from hypothesis import given, assume
from hypothesis import strategies as st
import pytest

import reticula as ret

from network_strategies import (
    undirected_network, undirected_hypernetwork,
    directed_network, any_network)


@given(any_network)
def test_union_idempotency(net):
    assert ret.graph_union(net, net) == net


@given(directed_network(self_loops=False))
def test_sum_of_degrees_and_edge_counts(net):
    sum_degs = sum(net.degree(v) for v in net.vertices())
    assert sum_degs == 2*len(net.edges())


@given(any_network)
def test_copy_equivalency(net):
    assert type(net)(net.edges(), net.vertices()) == net


@given(st.data(), any_network)
def test_union_vertex_subgraph_equivalency(data, net):
    assume(net.vertices())
    verts = data.draw(st.lists(st.sampled_from(net.vertices())))
    assert ret.graph_union(net, ret.vertex_induced_subgraph(net, verts)) == net


@given(st.data(), any_network)
def test_union_edge_subgraph_equivalency(data, net):
    assume(net.edges())
    edges = data.draw(st.lists(st.sampled_from(net.edges())))
    assert ret.graph_union(net, ret.edge_induced_subgraph(net, edges)) == net


@given(undirected_network())
def test_union_components_equivalency(net):
    assert {v for comp in ret.connected_components(net)
            for v in comp} == set(net.vertices())


@given(st.one_of(undirected_network(), undirected_hypernetwork()))
def test_degree_assortativity(net):
    assume(len(net.edges()) > 2)
    d1 = []
    d2 = []
    for e in net.edges():
        for i in e.mutator_verts():
            for j in e.mutated_verts():
                if i != j:
                    d1.append(net.degree(i))
                    d2.append(net.degree(j))

    def is_constant(d):
        if not d:
            return True  # Consider empty list as constant
        first_element = d[0]
        return all(element == first_element for element in d)

    import warnings
    with warnings.catch_warnings():
        warnings.simplefilter("ignore")

        sp = float("nan")
        if len(d1) > 1 and not is_constant(d1) and not is_constant(d2):
            sp = statistics.correlation(d1, d2)
    r = ret.degree_assortativity(net)
    print(d1, d2, sp, r)

    assert (math.isnan(sp) and math.isnan(r)) or sp == pytest.approx(r)


@given(undirected_network())
def test_connected_components(net):
    ccs = ret.connected_components(net)

    # check that it is a partition
    assert set(net.vertices()) == set().union(*ccs)

    lcc = ret.largest_connected_component(net)
    if ccs:
        assert lcc == max(ccs, key=len)
    else:
        assert list(lcc) == []

    connected_subgraph = ret.vertex_induced_subgraph(net, lcc)
    assert ret.is_connected(connected_subgraph)

    from itertools import product
    for cc in ccs:
        for v in cc:
            assert ret.connected_component(net, v) == cc

        for v1, v2 in product(cc, repeat=2):
            assert ret.is_reachable(net, v1, v2)

    from itertools import combinations
    for c1, c2 in combinations(ccs, r=2):
        for v1, v2 in product(c1, c2):
            assert not ret.is_reachable(net, v1, v2)
            assert not ret.is_reachable(net, v2, v1)


@given(undirected_network(self_loops=False))
def test_graphicality(net):
    degs = ret.degree_sequence(net)
    assert ret.is_graphic(degs)


@given(directed_network(self_loops=False))
def test_digraphicality(net):
    degs = ret.in_out_degree_pair_sequence(net)
    assert ret.is_digraphic(degs)
