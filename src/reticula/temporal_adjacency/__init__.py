import sys as _sys

from .. import _generic_attribute
from ..reticula_ext import temporal_adjacency as _reticula_ext_adj

_temporal_edge_types = set()

_generic_adjacency_attrs = [
        "simple",
        "limited_waiting_time",
        "exponential",
        "geometric"]
for _a in _generic_adjacency_attrs:
    setattr(_sys.modules[__name__],
            _a, _generic_attribute(
                _a, [_temporal_edge_types],
                module=_reticula_ext_adj))
