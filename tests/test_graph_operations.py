from hypothesis import given, assume, note, reproduce_failure
import math
import statistics

from hypothesis import strategies as st
import pytest

import reticula as ret


@st.composite
def undirected_network(draw: st.DrawFn,
                       min_verts: int = 0, max_verts: int = 50,
                       self_loops: bool = True):
    if min_verts < 0:
        raise ValueError("min_verts cannot be negative.")
    if max_verts < min_verts:
        raise ValueError("min_verts should not be larger than max_vert.")

    verts = list(range(
        draw(st.integers(min_value=min_verts, max_value=max_verts))))

    max_edges = len(verts)*(len(verts)-1)//2
    if self_loops:
        max_edges += len(verts)

    edges = st.lists(
        st.tuples(
            st.integers(min_value=0, max_value=len(verts)),
            st.integers(min_value=0, max_value=len(verts))).filter(
            lambda e: e[0] != e[1] or self_loops),
        min_size=0, max_size=max_edges)

    return ret.undirected_network[ret.int64](draw(edges), verts)


@given(undirected_network())
def test_union_idempotency(net):
    assert ret.graph_union(net, net) == net


@given(undirected_network(self_loops=False))
def test_sum_of_degrees_and_edge_counts(net):
    sum_degs = sum(net.degree(v) for v in net.vertices())
    assert sum_degs == 2*len(net.edges())


@given(undirected_network())
def test_copy_equivalency(net):
    assert type(net)(net.edges(), net.vertices()) == net


@given(st.data(), undirected_network())
def test_union_vertex_subgraph_equivalency(data, net):
    assume(net.vertices())
    verts = data.draw(st.lists(st.sampled_from(net.vertices())))
    assert ret.graph_union(net, ret.vertex_induced_subgraph(net, verts)) == net


@given(st.data(), undirected_network())
def test_union_edge_subgraph_equivalency(data, net):
    assume(net.edges())
    edges = data.draw(st.lists(st.sampled_from(net.edges())))
    assert ret.graph_union(net, ret.edge_induced_subgraph(net, edges)) == net


@given(undirected_network())
def test_union_components_equivalency(net):
    assert {v for comp in ret.connected_components(net)
            for v in comp} == set(net.vertices())


@given(undirected_network())
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


@given(undirected_network(max_verts=30))
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
