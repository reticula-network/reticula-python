#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>
#include <dag/dag.hpp>

#include "type_str.hpp"

namespace py = pybind11;

template <typename VertT>
void declare_directed_network_algorithms(py::module& m) {
    m.def(("topological_order_"+type_str<VertT>{}()).c_str(),
        &dag::topological_order<VertT>);

    m.def(("out_component_"+type_str<VertT>{}()).c_str(),
        &dag::out_component<VertT>);

    m.def(("in_component_"+type_str<VertT>{}()).c_str(),
        &dag::in_component<VertT>);

    m.def(("weakly_connected_component_"+type_str<VertT>{}()).c_str(),
        &dag::weakly_connected_component<VertT>);
}


template <typename VertT1, template VertT2>
void declare_relabel_nodes(py::module& m) {
    m.def(fmt::format("relable_nodes_{}_{}",
            type_str<VertT1>{}(), type_str<VertT2>{}()).c_str(),
        &dag::cartesian_product<VertT1, VertT2>);
}

template <typename VertT1, template VertT2>
void cartesian_product(py::module& m) {
    m.def(fmt::format("cartesian_product_{}_{}",
            type_str<VertT1>{}(), type_str<VertT2>{}()).c_str(),
        &dag::cartesian_product<VertT1, VertT2>);
}

void declare_typed_algorithms(py::module& m) {
    declare_directed_network_algorithms<int8_t>(m)
    declare_directed_network_algorithms<int16_t>(m)
    declare_directed_network_algorithms<int32_t>(m)
    declare_directed_network_algorithms<int64_t>(m)
    declare_directed_network_algorithms<uint8_t>(m)
    declare_directed_network_algorithms<uint16_t>(m)
    declare_directed_network_algorithms<uint32_t>(m)
    declare_directed_network_algorithms<uint64_t>(m)
    declare_directed_network_algorithms<std::string>(m)

    declare_relabel_nodes<int8_t, int8_t>(m)
    declare_relabel_nodes<int8_t, int16_t>(m)
    declare_relabel_nodes<int8_t, int32_t>(m)
    declare_relabel_nodes<int8_t, int64_t>(m)
    declare_relabel_nodes<int8_t, uint8_t>(m)
    declare_relabel_nodes<int8_t, uint16_t>(m)
    declare_relabel_nodes<int8_t, uint32_t>(m)
    declare_relabel_nodes<int8_t, uint64_t>(m)

    declare_relabel_nodes<int16_t, int8_t>(m)
    declare_relabel_nodes<int16_t, int16_t>(m)
    declare_relabel_nodes<int16_t, int32_t>(m)
    declare_relabel_nodes<int16_t, int64_t>(m)
    declare_relabel_nodes<int16_t, uint8_t>(m)
    declare_relabel_nodes<int16_t, uint16_t>(m)
    declare_relabel_nodes<int16_t, uint32_t>(m)
    declare_relabel_nodes<int16_t, uint64_t>(m)

    declare_relabel_nodes<int32_t, int8_t>(m)
    declare_relabel_nodes<int32_t, int16_t>(m)
    declare_relabel_nodes<int32_t, int32_t>(m)
    declare_relabel_nodes<int32_t, int64_t>(m)
    declare_relabel_nodes<int32_t, uint8_t>(m)
    declare_relabel_nodes<int32_t, uint16_t>(m)
    declare_relabel_nodes<int32_t, uint32_t>(m)
    declare_relabel_nodes<int32_t, uint64_t>(m)

    declare_relabel_nodes<int64_t, int8_t>(m)
    declare_relabel_nodes<int64_t, int16_t>(m)
    declare_relabel_nodes<int64_t, int32_t>(m)
    declare_relabel_nodes<int64_t, int64_t>(m)
    declare_relabel_nodes<int64_t, uint8_t>(m)
    declare_relabel_nodes<int64_t, uint16_t>(m)
    declare_relabel_nodes<int64_t, uint32_t>(m)
    declare_relabel_nodes<int64_t, uint64_t>(m)

    declare_relabel_nodes<uint8_t, int8_t>(m)
    declare_relabel_nodes<uint8_t, int16_t>(m)
    declare_relabel_nodes<uint8_t, int32_t>(m)
    declare_relabel_nodes<uint8_t, int64_t>(m)
    declare_relabel_nodes<uint8_t, uint8_t>(m)
    declare_relabel_nodes<uint8_t, uint16_t>(m)
    declare_relabel_nodes<uint8_t, uint32_t>(m)
    declare_relabel_nodes<uint8_t, uint64_t>(m)

    declare_relabel_nodes<uint16_t, int8_t>(m)
    declare_relabel_nodes<uint16_t, int16_t>(m)
    declare_relabel_nodes<uint16_t, int32_t>(m)
    declare_relabel_nodes<uint16_t, int64_t>(m)
    declare_relabel_nodes<uint16_t, uint8_t>(m)
    declare_relabel_nodes<uint16_t, uint16_t>(m)
    declare_relabel_nodes<uint16_t, uint32_t>(m)
    declare_relabel_nodes<uint16_t, uint64_t>(m)

    declare_relabel_nodes<uint32_t, int8_t>(m)
    declare_relabel_nodes<uint32_t, int16_t>(m)
    declare_relabel_nodes<uint32_t, int32_t>(m)
    declare_relabel_nodes<uint32_t, int64_t>(m)
    declare_relabel_nodes<uint32_t, uint8_t>(m)
    declare_relabel_nodes<uint32_t, uint16_t>(m)
    declare_relabel_nodes<uint32_t, uint32_t>(m)
    declare_relabel_nodes<uint32_t, uint64_t>(m)

    declare_relabel_nodes<uint64_t, int8_t>(m)
    declare_relabel_nodes<uint64_t, int16_t>(m)
    declare_relabel_nodes<uint64_t, int32_t>(m)
    declare_relabel_nodes<uint64_t, int64_t>(m)
    declare_relabel_nodes<uint64_t, uint8_t>(m)
    declare_relabel_nodes<uint64_t, uint16_t>(m)
    declare_relabel_nodes<uint64_t, uint32_t>(m)
    declare_relabel_nodes<uint64_t, uint64_t>(m)

    declare_relabel_nodes<std::string, int8_t>(m)
    declare_relabel_nodes<std::string, int16_t>(m)
    declare_relabel_nodes<std::string, int32_t>(m)
    declare_relabel_nodes<std::string, int64_t>(m)
    declare_relabel_nodes<std::string, uint8_t>(m)
    declare_relabel_nodes<std::string, uint16_t>(m)
    declare_relabel_nodes<std::string, uint32_t>(m)
    declare_relabel_nodes<std::string, uint64_t>(m)
}
