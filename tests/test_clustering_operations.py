import pytest

import reticula as ret


def test_temporal_clusters():
    edges = [(0, 1, 1.0), (1, 2, 1.5), (2, 3, 2.0), (3, 4, 3.0)]
    net = ret.directed_temporal_network[ret.int64, ret.double](edges)
    adj = ret.temporal_adjacency.simple[net.edge_type()]()

    e = net.edge_type()(1, 2, 1.5)

    in_clusters = ret.in_clusters(net, adj)
    assert dict(in_clusters)[e].volume() == 2

    out_clusters = ret.out_clusters(net, adj)
    assert dict(out_clusters)[e].volume() == 3


def test_cluster_functions():
    edges = [(0, 1, 1.0), (1, 2, 1.5), (2, 3, 2.0), (3, 4, 3.0)]
    net = ret.directed_temporal_network[ret.int64, ret.double](edges)
    adj = ret.temporal_adjacency.simple[net.edge_type()]()

    in_cluster = ret.in_cluster(net, adj, 2, 1.5)
    assert in_cluster.volume() == 1

    out_cluster = ret.out_cluster(net, adj, 1, 1.5)
    assert out_cluster.volume() == 1


def test_cluster_sizes():
    edges = [(0, 1, 1.0), (1, 2, 1.5), (2, 3, 2.0), (3, 4, 3.0)]
    net = ret.directed_temporal_network[ret.int64, ret.double](edges)
    adj = ret.temporal_adjacency.simple[net.edge_type()]()

    e = net.edge_type()(1, 2, 1.5)

    in_sizes = ret.in_cluster_sizes(net, adj)
    assert dict(in_sizes)[e].volume() == 2

    out_sizes = ret.out_cluster_sizes(net, adj)
    assert dict(out_sizes)[e].volume() == 3


def test_cluster_size_estimates():
    edges = [(0, 1, 1.0), (1, 2, 1.5), (2, 3, 2.0), (3, 4, 3.0)]
    net = ret.directed_temporal_network[ret.int64, ret.double](edges)
    adj = ret.temporal_adjacency.simple[net.edge_type()]()

    e = net.edge_type()(1, 2, 1.5)

    in_sizes = ret.in_cluster_sizes(net, adj)
    assert dict(in_sizes)[e].volume() == pytest.approx(2, rel=0.1)

    out_sizes = ret.out_cluster_sizes(net, adj)
    assert dict(out_sizes)[e].volume() == pytest.approx(3, rel=0.1)
