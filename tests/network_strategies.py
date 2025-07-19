from hypothesis import strategies as st
import reticula as ret

# Shared integer vertex type
VERT = ret.int64
TIME = ret.double


@st.composite
def undirected_network(draw: st.DrawFn,
                       min_verts: int = 0, max_verts: int = 10,
                       self_loops: bool = True):
    if min_verts < 0:
        raise ValueError("min_verts cannot be negative")
    if max_verts < min_verts:
        raise ValueError("min_verts should not exceed max_verts")
    verts = list(
        range(draw(st.integers(min_value=min_verts, max_value=max_verts))))
    max_edges = len(verts)*(len(verts)-1)//2
    if self_loops:
        max_edges += len(verts)
    edges = st.lists(
        st.tuples(
            st.integers(min_value=0, max_value=len(verts)),
            st.integers(min_value=0, max_value=len(verts))).filter(
                lambda e: e[0] != e[1] or self_loops),
        min_size=0, max_size=max_edges)
    return ret.undirected_network[VERT](draw(edges), verts)


@st.composite
def directed_network(draw: st.DrawFn,
                     min_verts: int = 0, max_verts: int = 10,
                     self_loops: bool = True):
    if min_verts < 0:
        raise ValueError("min_verts cannot be negative")
    if max_verts < min_verts:
        raise ValueError("min_verts should not exceed max_verts")
    verts = list(
        range(draw(st.integers(min_value=min_verts, max_value=max_verts))))
    max_edges = len(verts)*(len(verts)-1)
    if self_loops:
        max_edges += len(verts)
    edges = st.lists(
        st.tuples(
            st.integers(min_value=0, max_value=len(verts)),
            st.integers(min_value=0, max_value=len(verts))).filter(
                lambda e: e[0] != e[1] or self_loops),
        min_size=0, max_size=max_edges)
    return ret.directed_network[VERT](draw(edges), verts)


@st.composite
def undirected_hypernetwork(draw: st.DrawFn,
                            min_verts: int = 0, max_verts: int = 10):
    if min_verts < 0:
        raise ValueError("min_verts cannot be negative")
    if max_verts < min_verts:
        raise ValueError("min_verts should not exceed max_verts")
    verts = list(
        range(draw(st.integers(min_value=min_verts, max_value=max_verts))))
    max_edges = len(verts)*2
    hyperedge = st.lists(st.integers(min_value=0, max_value=len(
        verts)), min_size=0, max_size=len(verts))
    edges = st.lists(hyperedge, min_size=0, max_size=max_edges)
    return ret.undirected_hypernetwork[VERT](draw(edges), verts)


@st.composite
def directed_hypernetwork(draw: st.DrawFn,
                          min_verts: int = 0, max_verts: int = 10):
    if min_verts < 0:
        raise ValueError("min_verts cannot be negative")
    if max_verts < min_verts:
        raise ValueError("min_verts should not exceed max_verts")
    verts = list(
        range(draw(st.integers(min_value=min_verts, max_value=max_verts))))
    max_edges = len(verts)*2
    vertex_list = st.lists(st.integers(
        min_value=0, max_value=len(verts)), min_size=0, max_size=len(verts))
    edge = st.tuples(vertex_list, vertex_list)
    edges = st.lists(edge, min_size=0, max_size=max_edges)
    return ret.directed_hypernetwork[VERT](draw(edges), verts)


@st.composite
def undirected_temporal_network(draw: st.DrawFn,
                                min_verts: int = 0, max_verts: int = 10,
                                self_loops: bool = True):
    verts = list(
        range(draw(st.integers(min_value=min_verts, max_value=max_verts))))
    max_edges = len(verts)*(len(verts)-1)//2
    if self_loops:
        max_edges += len(verts)
    edge = st.tuples(
        st.integers(min_value=0, max_value=len(verts)),
        st.integers(min_value=0, max_value=len(verts)),
        st.floats(min_value=0, max_value=10)).filter(
            lambda e: e[0] != e[1] or self_loops)
    edges = st.lists(edge, min_size=0, max_size=max_edges)
    return ret.undirected_temporal_network[VERT, TIME](draw(edges), verts)


@st.composite
def directed_temporal_network(draw: st.DrawFn,
                              min_verts: int = 0, max_verts: int = 10,
                              self_loops: bool = True):
    verts = list(
        range(draw(st.integers(min_value=min_verts, max_value=max_verts))))
    max_edges = len(verts)*(len(verts)-1)
    if self_loops:
        max_edges += len(verts)
    edge = st.tuples(
        st.integers(min_value=0, max_value=len(verts)),
        st.integers(min_value=0, max_value=len(verts)),
        st.floats(min_value=0, max_value=10)).filter(
            lambda e: e[0] != e[1] or self_loops)
    edges = st.lists(edge, min_size=0, max_size=max_edges)
    return ret.directed_temporal_network[VERT, TIME](draw(edges), verts)


@st.composite
def undirected_temporal_hypernetwork(draw: st.DrawFn,
                                     min_verts: int = 0, max_verts: int = 10):
    verts = list(
        range(draw(st.integers(min_value=min_verts, max_value=max_verts))))
    max_edges = len(verts)*2
    hyperedge = st.tuples(
        st.lists(st.integers(min_value=0, max_value=len(verts)),
                 min_size=0, max_size=len(verts)),
        st.floats(min_value=0, max_value=10))
    edges = st.lists(hyperedge, min_size=0, max_size=max_edges)
    return ret.undirected_temporal_hypernetwork[VERT, TIME](draw(edges), verts)


@st.composite
def directed_temporal_hypernetwork(draw: st.DrawFn,
                                   min_verts: int = 0, max_verts: int = 10):
    verts = list(
        range(draw(st.integers(min_value=min_verts, max_value=max_verts))))
    max_edges = len(verts)*2
    vertex_list = st.lists(st.integers(
        min_value=0, max_value=len(verts)), min_size=0, max_size=len(verts))
    hyperedge = st.tuples(vertex_list, vertex_list,
                          st.floats(min_value=0, max_value=10))
    edges = st.lists(hyperedge, min_size=0, max_size=max_edges)
    return ret.directed_temporal_hypernetwork[VERT, TIME](draw(edges), verts)
