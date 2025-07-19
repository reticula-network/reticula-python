import reticula as ret


def test_path_graph():
    g = ret.path_graph[ret.int64](size=4)
    assert len(g.vertices()) == 4
    assert len(g.edges()) == 3
    assert ret.is_connected(g)


def test_cycle_graph():
    g = ret.cycle_graph[ret.int64](size=5)
    assert len(g.vertices()) == 5
    assert len(g.edges()) == 5


def test_complete_graph():
    g = ret.complete_graph[ret.int64](size=4)
    assert len(g.vertices()) == 4
    assert len(g.edges()) == 6


def test_complete_directed_graph():
    g = ret.complete_directed_graph[ret.int64](size=3)
    assert len(g.vertices()) == 3
    assert len(g.edges()) == 6


def test_random_gnp_graph():
    gen = ret.mersenne_twister(42)
    g = ret.random_gnp_graph[ret.int64](n=5, p=0.5, random_state=gen)
    assert len(g.vertices()) == 5
    assert 0 <= len(g.edges()) <= 10


def test_random_directed_gnp_graph():
    gen = ret.mersenne_twister(42)
    g = ret.random_directed_gnp_graph[ret.int64](n=4, p=0.5, random_state=gen)
    assert len(g.vertices()) == 4
    assert 0 <= len(g.edges()) <= 12


def test_random_regular_graph():
    gen = ret.mersenne_twister(42)
    g = ret.random_regular_graph[ret.int64](size=6, degree=2, random_state=gen)
    assert len(g.vertices()) == 6
    assert all(g.degree(v) == 2 for v in g.vertices())


def test_add_remove_edges_vertices():
    g = ret.path_graph[ret.int64](size=3)
    g2 = ret.with_edges(g, [(0, 2)])
    assert len(g2.edges()) == len(g.edges()) + 1
    g3 = ret.without_edges(g2, [(0, 2)])
    assert g3 == g

    g4 = ret.with_vertices(g, [3, 4])
    assert set(g4.vertices()) == set(g.vertices()) | {3, 4}
    g5 = ret.without_vertices(g4, [3, 4])
    assert g5 == g


def test_subgraph_operations():
    g = ret.cycle_graph[ret.int64](size=4)
    edges = g.edges()[:2]
    sub_e = ret.edge_induced_subgraph(g, edges)
    assert set(sub_e.edges()) == set(edges)

    verts = g.vertices()[:3]
    sub_v = ret.vertex_induced_subgraph(g, verts)
    assert set(sub_v.vertices()) == set(verts)
    for e in sub_v.edges():
        assert set(e.incident_verts()).issubset(set(verts))


def test_graph_union():
    g1 = ret.path_graph[ret.int64](size=3)
    g2 = ret.with_edges(g1, [(0, 2)])
    u = ret.graph_union(g1, g2)
    assert len(u.edges()) == len(g1.edges()) + 1
    assert set(u.vertices()) == set(g2.vertices())
