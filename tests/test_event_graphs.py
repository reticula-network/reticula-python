import reticula as ret


def test_event_graph_creation():
    edges = [(0, 1, 1.0), (1, 2, 2.0), (0, 2, 3.0)]
    net = ret.directed_temporal_network[ret.int64, ret.double](edges)

    adj = ret.temporal_adjacency.limited_waiting_time[net.edge_type()](2.0)
    eg = ret.event_graph(net, adj)
    assert eg.successors((1, 2, 2.0)) == []
    assert eg.successors((0, 1, 1.0)) == [net.edge_type()(1, 2, 2.0)]
    assert eg.predecessors((1, 2, 2.0)) == [net.edge_type()(0, 1, 1.0)]

    adj = ret.temporal_adjacency.limited_waiting_time[net.edge_type()](0.5)
    eg = ret.event_graph(net, adj)
    assert eg.successors((1, 2, 2.0)) == []
    assert eg.predecessors((1, 2, 2.0)) == []


def test_implicit_event_graph():
    edges = [(0, 1, 1.0), (1, 2, 2.0), (0, 2, 3.0)]
    net = ret.directed_temporal_network[ret.int64, ret.double](edges)

    adj = ret.temporal_adjacency.limited_waiting_time[net.edge_type()](2.0)
    ieg = ret.implicit_event_graph[net.edge_type(), type(adj)](net, adj)
    assert ieg.successors((1, 2, 2.0)) == []
    assert ieg.successors((0, 1, 1.0)) == [net.edge_type()(1, 2, 2.0)]
    assert ieg.predecessors((1, 2, 2.0)) == [net.edge_type()(0, 1, 1.0)]

    ieg = ret.make_implicit_event_graph(net, adj)
    assert ieg.successors((1, 2, 2.0)) == []
    assert ieg.successors((0, 1, 1.0)) == [net.edge_type()(1, 2, 2.0)]
    assert ieg.predecessors((1, 2, 2.0)) == [net.edge_type()(0, 1, 1.0)]

    adj = ret.temporal_adjacency.limited_waiting_time[net.edge_type()](0.5)
    ieg = ret.implicit_event_graph[net.edge_type(), type(adj)](net, adj)
    assert ieg.successors((1, 2, 2.0)) == []
    assert ieg.predecessors((1, 2, 2.0)) == []

    ieg = ret.make_implicit_event_graph(net, adj)
    assert ieg.successors((1, 2, 2.0)) == []
    assert ieg.predecessors((1, 2, 2.0)) == []
