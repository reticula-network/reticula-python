import reticula as ret


def test_temporal_edge_creation():
    edge = ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 1.5)
    assert set(edge.incident_verts()) == {0, 1}
    assert set(edge.mutator_verts()) == {0, 1}
    assert set(edge.mutated_verts()) == {0, 1}
    assert edge.cause_time() == 1.5
    assert edge.effect_time() == 1.5

    edge = ret.directed_temporal_edge[ret.int64, ret.double](0, 1, 2.0)
    assert set(edge.incident_verts()) == {0, 1}
    assert edge.mutator_verts() == [0]
    assert edge.mutated_verts() == [1]
    assert edge.cause_time() == 2.0
    assert edge.effect_time() == 2.0


def test_delayed_temporal_edge():
    edge = ret.directed_delayed_temporal_edge[ret.int64, ret.double](
        0, 1, 1.0, 2.0)
    assert set(edge.incident_verts()) == {0, 1}
    assert edge.mutator_verts() == [0]
    assert edge.mutated_verts() == [1]
    assert edge.cause_time() == 1.0
    assert edge.effect_time() == 2.0


def test_temporal_network_creation():
    edges = [
        ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 1.0),
        ret.undirected_temporal_edge[ret.int64, ret.double](1, 2, 2.0)
    ]
    net = ret.undirected_temporal_network[ret.int64, ret.double](edges)
    assert len(net.edges()) == 2
    assert len(net.vertices()) == 3

    net = ret.undirected_temporal_network[ret.int64, ret.double](
        edges, verts=[5])
    assert len(net.edges()) == 2
    assert len(net.vertices()) == 4


def test_temporal_hyperedge():
    edge = ret.undirected_temporal_hyperedge[ret.int64, ret.double](
        [0, 1, 2], 1.5)
    assert set(edge.incident_verts()) == {0, 1, 2}
    assert edge.cause_time() == 1.5


def test_temporal_hypernetwork():
    edges = [
        ret.undirected_temporal_hyperedge[ret.int64, ret.double]([
            0, 1, 2], 1.0),
        ret.undirected_temporal_hyperedge[ret.int64, ret.double]([
            1, 2, 3], 2.0)
    ]
    net = ret.undirected_temporal_hypernetwork[ret.int64, ret.double](edges)
    assert len(net.edges()) == 2
    assert len(net.vertices()) == 4


def test_link_timeline():
    edges = [
        ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 1.0),
        ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 2.0),
        ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 3.0)
    ]
    net = ret.undirected_temporal_network[ret.int64, ret.double](edges)

    static_edge = ret.undirected_edge[ret.int64](0, 1)
    timeline = ret.link_timeline(net, static_edge)
    assert len(timeline) == 3
    times = [edge.cause_time() for edge in timeline]
    assert 1.0 in times
    assert 2.0 in times
    assert 3.0 in times


def test_link_timelines():
    edges = [
        ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 1.0),
        ret.undirected_temporal_edge[ret.int64, ret.double](1, 2, 2.0)
    ]
    net = ret.undirected_temporal_network[ret.int64, ret.double](edges)

    timelines = ret.link_timelines(net)
    assert len(timelines) == 2


def test_static_projection():
    edges = [
        ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 1.0),
        ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 2.0),
        ret.undirected_temporal_edge[ret.int64, ret.double](1, 2, 3.0)
    ]
    net = ret.undirected_temporal_network[ret.int64, ret.double](edges)

    static_net = ret.static_projection(net)
    assert len(static_net.vertices()) == 3
    assert len(static_net.edges()) == 2


def test_time_window():
    edges = [ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 2.0)]
    net = ret.undirected_temporal_network[ret.int64, ret.double](edges)
    window = ret.time_window(net)
    assert window[0] <= 2.0 <= window[1]


def test_cause_effect_time_windows():
    edge = ret.directed_delayed_temporal_edge[ret.int64, ret.double](
        0, 1, 1.0, 2.0)
    net = ret.directed_delayed_temporal_network[ret.int64, ret.double]([edge])

    cause_window = ret.cause_time_window(net)
    effect_window = ret.effect_time_window(net)

    assert cause_window[0] <= 1.0 <= cause_window[1]
    assert effect_window[0] <= 2.0 <= effect_window[1]


def test_temporal_adjacency():
    adj_func = ret.temporal_adjacency.simple[
        ret.directed_temporal_edge[ret.int64, ret.double]]()
    assert adj_func is not None


def test_is_temporal_edge():
    temp_edge = ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 1.0)
    static_edge = ret.undirected_edge[ret.int64](0, 1)

    assert ret.is_temporal_edge(temp_edge)
    assert not ret.is_temporal_edge(static_edge)


def test_is_static_edge():
    temp_edge = ret.undirected_temporal_edge[ret.int64, ret.double](0, 1, 1.0)
    static_edge = ret.undirected_edge[ret.int64](0, 1)

    assert not ret.is_static_edge(temp_edge)
    assert ret.is_static_edge(static_edge)


def test_is_instantaneous():
    instant_edge = ret.undirected_temporal_edge[ret.int64, ret.double](
        0, 1, 1.0)
    delayed_edge = ret.directed_delayed_temporal_edge[ret.int64, ret.double](
        0, 1, 1.0, 2.0)

    assert ret.is_instantaneous(instant_edge)
    assert not ret.is_instantaneous(delayed_edge)
