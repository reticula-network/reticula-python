#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <dag/dag.hpp>

#include "type_str.hpp"

namespace py = pybind11;

template <typename VertT>
void declare_generators(py::module& m) {
    m.def(("square_grid_graph_"+type_str<VertT>{}()).c_str(),
        &dag::square_grid_graph<VertT>);

    m.def(("path_graph_"+type_str<VertT>{}()).c_str(),
        &dag::path_graph<VertT>);

    m.def(("cycle_graph_"+type_str<VertT>{}()).c_str(),
        &dag::cycle_graph<VertT>);

    m.def(("regular_ring_lattice_"+type_str<VertT>{}()).c_str(),
        &dag::regular_ring_lattice<VertT>);
}


void declare_typed_generators(py::module& m) {
    declare_generators<int8_t>(m);
    declare_generators<int16_t>(m);
    declare_generators<int32_t>(m);
    declare_generators<int64_t>(m);

    declare_generators<uint8_t>(m);
    declare_generators<uint16_t>(m);
    declare_generators<uint32_t>(m);
    declare_generators<uint64_t>(m);
}
