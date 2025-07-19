import tempfile
import os

from hypothesis import given, assume, strategies as st
import networkx as nx

import reticula as ret

from network_strategies import (
    any_dyadic_network, undirected_network, directed_network)


@given(any_dyadic_network)
def test_write_read_edgelist(g):
    assume(len(g.edges()) > 0)
    with tempfile.NamedTemporaryFile(
            mode='w', delete=False, suffix='.txt') as f:
        temp_path = f.name

    try:
        ret.write_edgelist(g, temp_path)

        assert os.path.exists(temp_path)
        with open(temp_path, 'r') as f:
            content = f.read()
            lines = content.strip().split('\n')
            assert len(lines) == len(g.edges())

    finally:
        os.unlink(temp_path)


@given(st.one_of(undirected_network(), directed_network()))
def test_to_from_networkx(g):
    nx_g = ret.to_networkx(g)
    assert isinstance(nx_g, nx.Graph)

    g_back = ret.from_networkx[ret.int64](nx_g)
    assert g_back == g
