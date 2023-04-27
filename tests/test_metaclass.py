import reticula as ret


def test_metaclass_repr():
    assert repr(ret.int64) == "<class 'int64'>"
    assert repr(ret.undirected_network[ret.int64]) == \
        "<class 'undirected_network[int64]'>"
    assert repr(ret.undirected_temporal_network[ret.int64, ret.double]) == \
        "<class 'undirected_temporal_network[int64, double]'>"
