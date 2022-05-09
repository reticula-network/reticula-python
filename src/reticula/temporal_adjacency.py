import sys as _sys

from .generic_attribute import generic_attribute as _generic_attribute
from .reticula_ext import temporal_adjacency as _reticula_ext_adj

_temporal_edge_types = set()

_generic_adjacency_attrs = [
        "simple",
        "limited_waiting_time",
        "exponential",
        "geometric"]
for _a in _generic_adjacency_attrs:
    setattr(_sys.modules[__name__],
            _a, _generic_attribute(
                attr_prefix=_a,
                arg_names=("temporal_edge_types",),
                options=((t,) for t in _temporal_edge_types),
                function_module=_reticula_ext_adj,
                api_module_name=__name__))
