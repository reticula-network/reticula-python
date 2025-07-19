import reticula as ret


def test_edge_creation():
    edge = ret.undirected_edge[ret.int64](0, 1)
    assert set(edge.incident_verts()) == {0, 1}
    assert set(edge.mutator_verts()) == {0, 1}
    assert set(edge.mutated_verts()) == {0, 1}

    edge = ret.directed_edge[ret.int64](0, 1)
    assert set(edge.incident_verts()) == {0, 1}
    assert edge.mutator_verts() == [0]
    assert edge.mutated_verts() == [1]


def test_hyperedge_creation():
    edge = ret.undirected_hyperedge[ret.int64]([0, 1, 2])
    assert set(edge.incident_verts()) == {0, 1, 2}

    edge = ret.directed_hyperedge[ret.int64]([0, 1], [2, 3])
    assert set(edge.mutator_verts()) == {0, 1}
    assert set(edge.mutated_verts()) == {2, 3}
    assert set(edge.incident_verts()) == {0, 1, 2, 3}


def test_edge_degree_functions():
    edge = ret.directed_edge[ret.int64](0, 1)
    assert ret.edge_in_degree(edge) == 1
    assert ret.edge_out_degree(edge) == 1
    assert ret.edge_incident_degree(edge) == 2

    edge = ret.directed_hyperedge[ret.int64]([0, 1, 2], [2, 3, 4, 5])
    assert ret.edge_in_degree(edge) == 3
    assert ret.edge_out_degree(edge) == 4
    assert ret.edge_incident_degree(edge) == 6

    edge = ret.undirected_edge[ret.int64](0, 1)
    assert ret.edge_degree(edge) == 2
    assert ret.edge_in_degree(edge) == 2
    assert ret.edge_out_degree(edge) == 2
    assert ret.edge_incident_degree(edge) == 2


def test_is_network_edge():
    existing_edge = ret.undirected_edge[ret.int64](0, 1)
    non_existing_edge = ret.undirected_edge[ret.int64](1, 3)

    assert ret.is_network_edge(existing_edge)
    assert ret.is_network_edge(non_existing_edge)


def test_is_directed_undirected():
    directed_edge = ret.directed_edge[ret.int64](0, 1)
    undirected_edge = ret.undirected_edge[ret.int64](0, 1)

    assert ret.is_directed(directed_edge)
    assert not ret.is_directed(undirected_edge)

    assert not ret.is_undirected(directed_edge)
    assert ret.is_undirected(undirected_edge)


def test_is_dyadic():
    edge = ret.undirected_edge[ret.int64](0, 1)
    assert ret.is_dyadic(edge)

    hyperedge = ret.undirected_hyperedge[ret.int64]([0, 1, 2])
    assert not ret.is_dyadic(hyperedge)
