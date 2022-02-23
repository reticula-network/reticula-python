import sys

from .. import generic_attribute
from ...dag_ext import temporal_adjacency as dag_ext_adj

temporal_edge_types = set()

generic_adjacency_attrs = [
        "simple",
        "limited_waiting_time",
        "exponential",
        "geometric"]
for a in generic_adjacency_attrs:
    setattr(sys.modules[__name__],
            a, generic_attribute(
                a, [temporal_edge_types],
                module=dag_ext_adj))
