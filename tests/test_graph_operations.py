from hypothesis import strategies as st

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

from hypothesis import given, assume, note

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
