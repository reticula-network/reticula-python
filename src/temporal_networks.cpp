#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>
#include <dag/dag.hpp>

#include "type_str.hpp"

namespace py = pybind11;

template <typename VertT, typename TimeT>
void declare_temporal_networks(py::module &m) {
    using UndirectedTemporalNet = dag::undirected_temporal_network<VertT, TimeT>;
    py::class_<UndirectedTemporalNet>(m,
            type_str<UndirectedTemporalNet>{}().c_str())
        .def(py::init<std::vector<typename UndirectedTemporalNet::EdgeType>>())
        .def(py::init<std::vector<typename UndirectedTemporalNet::EdgeType>,
                std::vector<VertT>>())
        .def("vertices",       &UndirectedTemporalNet::vertices)
        .def("edges",          &UndirectedTemporalNet::edges)
        .def("edges_cause",    &UndirectedTemporalNet::edges_cause)
        .def("edges_effect",   &UndirectedTemporalNet::edges_effect)
        .def("incident_edges", &UndirectedTemporalNet::incident_edges)
        .def("in_degree",      &UndirectedTemporalNet::in_degree)
        .def("out_degree",     &UndirectedTemporalNet::out_degree)
        .def("degree",         &UndirectedTemporalNet::degree)
        .def("predecessors",   &UndirectedTemporalNet::predecessors)
        .def("successors",     &UndirectedTemporalNet::successors)
        .def("neighbours",     &UndirectedTemporalNet::neighbours)
        .def("in_edges",
            py::overload_cast<const VertT&>(
                &UndirectedTemporalNet::in_edges, py::const_))
        .def("out_edges",
            py::overload_cast<const VertT&>(
                &UndirectedTemporalNet::out_edges, py::const_))
        .def("in_edges",
            py::overload_cast<>(&UndirectedTemporalNet::in_edges, py::const_))
        .def("out_edges",
            py::overload_cast<>(&UndirectedTemporalNet::out_edges, py::const_))
        .def("__repr__", [](const UndirectedTemporalNet& a) {
            return fmt::format("<dag.{} {} verts {} edges>",
                type_str<UndirectedTemporalNet>{}(),
                a.vertices().size(), a.edges().size());
        });

    using DirectedTemporalNet = dag::directed_temporal_network<VertT, TimeT>;
    py::class_<DirectedTemporalNet>(m,
            type_str<DirectedTemporalNet>{}().c_str())
        .def(py::init<std::vector<typename DirectedTemporalNet::EdgeType>>())
        .def(py::init<std::vector<typename DirectedTemporalNet::EdgeType>,
                std::vector<VertT>>())
        .def("vertices",       &DirectedTemporalNet::vertices)
        .def("edges",          &DirectedTemporalNet::edges)
        .def("edges_cause",    &DirectedTemporalNet::edges_cause)
        .def("edges_effect",   &DirectedTemporalNet::edges_effect)
        .def("incident_edges", &DirectedTemporalNet::incident_edges)
        .def("in_degree",      &DirectedTemporalNet::in_degree)
        .def("out_degree",     &DirectedTemporalNet::out_degree)
        .def("degree",         &DirectedTemporalNet::degree)
        .def("predecessors",   &DirectedTemporalNet::predecessors)
        .def("successors",     &DirectedTemporalNet::successors)
        .def("neighbours",     &DirectedTemporalNet::neighbours)
        .def("in_edges",
            py::overload_cast<const VertT&>(
                &DirectedTemporalNet::in_edges, py::const_))
        .def("out_edges",
            py::overload_cast<const VertT&>(
                &DirectedTemporalNet::out_edges, py::const_))
        .def("in_edges",
            py::overload_cast<>(&DirectedTemporalNet::in_edges, py::const_))
        .def("out_edges",
            py::overload_cast<>(&DirectedTemporalNet::out_edges, py::const_))
        .def("__repr__", [](const DirectedTemporalNet& a) {
            return fmt::format("<dag.{} {} verts {} edges>",
                type_str<DirectedTemporalNet>{}(),
                a.vertices().size(), a.edges().size());
        });

    using DelayedTemporalNet =
         dag::directed_delayed_temporal_network<VertT, TimeT>;
    py::class_<DelayedTemporalNet>(m,
            type_str<DelayedTemporalNet>{}().c_str())
        .def(py::init<std::vector<typename DelayedTemporalNet::EdgeType>>())
        .def(py::init<std::vector<typename DelayedTemporalNet::EdgeType>,
                std::vector<VertT>>())
        .def("vertices",       &DelayedTemporalNet::vertices)
        .def("edges",          &DelayedTemporalNet::edges)
        .def("edges_cause",    &DelayedTemporalNet::edges_cause)
        .def("edges_effect",   &DelayedTemporalNet::edges_effect)
        .def("incident_edges", &DelayedTemporalNet::incident_edges)
        .def("in_degree",      &DelayedTemporalNet::in_degree)
        .def("out_degree",     &DelayedTemporalNet::out_degree)
        .def("degree",         &DelayedTemporalNet::degree)
        .def("predecessors",   &DelayedTemporalNet::predecessors)
        .def("successors",     &DelayedTemporalNet::successors)
        .def("neighbours",     &DelayedTemporalNet::neighbours)
        .def("in_edges",
            py::overload_cast<const VertT&>(
                &DelayedTemporalNet::in_edges, py::const_))
        .def("out_edges",
            py::overload_cast<const VertT&>(
                &DelayedTemporalNet::out_edges, py::const_))
        .def("in_edges",
            py::overload_cast<>(&DelayedTemporalNet::in_edges, py::const_))
        .def("out_edges",
            py::overload_cast<>(&DelayedTemporalNet::out_edges, py::const_))
        .def("__repr__", [](const DelayedTemporalNet& a) {
            return fmt::format("<dag.{} {} verts {} edges>",
                type_str<DelayedTemporalNet>{}(),
                a.vertices().size(), a.edges().size());
        });
}

void declare_typed_temporal_networks(py::module& m) {
    declare_temporal_networks<int8_t, float>(m);
    declare_temporal_networks<int8_t, double>(m);
    declare_temporal_networks<int8_t, long double>(m);
    declare_temporal_networks<int16_t, float>(m);
    declare_temporal_networks<int16_t, double>(m);
    declare_temporal_networks<int16_t, long double>(m);
    declare_temporal_networks<int32_t, float>(m);
    declare_temporal_networks<int32_t, double>(m);
    declare_temporal_networks<int32_t, long double>(m);
    declare_temporal_networks<int64_t, float>(m);
    declare_temporal_networks<int64_t, double>(m);
    declare_temporal_networks<int64_t, long double>(m);

    declare_temporal_networks<uint8_t, float>(m);
    declare_temporal_networks<uint8_t, double>(m);
    declare_temporal_networks<uint8_t, long double>(m);
    declare_temporal_networks<uint16_t, float>(m);
    declare_temporal_networks<uint16_t, double>(m);
    declare_temporal_networks<uint16_t, long double>(m);
    declare_temporal_networks<uint32_t, float>(m);
    declare_temporal_networks<uint32_t, double>(m);
    declare_temporal_networks<uint32_t, long double>(m);
    declare_temporal_networks<uint64_t, float>(m);
    declare_temporal_networks<uint64_t, double>(m);
    declare_temporal_networks<uint64_t, long double>(m);

    declare_temporal_networks<std::string, float>(m);
    declare_temporal_networks<std::string, double>(m);
    declare_temporal_networks<std::string, long double>(m);
}
