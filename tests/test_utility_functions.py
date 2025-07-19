import reticula as ret

from hypothesis import given
from network_strategies import undirected_network


@given(undirected_network())
def test_relabel_nodes(g):
    g_relabeled = ret.relabel_nodes[ret.int64](g)

    assert set(g_relabeled.vertices()) == \
        set(range(len(g_relabeled.vertices())))
    assert len(g_relabeled.edges()) == len(g.edges())


def test_cartesian_product():
    g1 = ret.path_graph[ret.int64](size=3)
    g2 = ret.path_graph[ret.int64](size=2)

    product = ret.cartesian_product(g1, g2)

    assert len(product.vertices()) == 6

    for v in product.vertices():
        assert isinstance(v, tuple)
        assert len(v) == 2


def test_string_type():
    g = ret.undirected_network[ret.string]([
        ("a", "b"),
        ("b", "c")
    ])
    assert len(g.vertices()) == 3
    assert len(g.edges()) == 2

    vertices = list(g.vertices())
    assert "a" in vertices
    assert "b" in vertices
    assert "c" in vertices
