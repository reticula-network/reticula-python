#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>
#include <dag/dag.hpp>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_networks {
  void operator()(py::module &m) {
    using UndirectedTemporalNet = dag::undirected_temporal_network<VertT, TimeT>;
    py::class_<UndirectedTemporalNet>(m,
        type_str<UndirectedTemporalNet>{}().c_str())
      .def(py::init<std::vector<typename UndirectedTemporalNet::EdgeType>>(),
          "edges"_a)
      .def(py::init<
            std::vector<typename UndirectedTemporalNet::EdgeType>,
            std::vector<VertT>>(),
          "edges"_a, "verts"_a)
      .def("vertices",       &UndirectedTemporalNet::vertices)
      .def("edges",          &UndirectedTemporalNet::edges)
      .def("edges_cause",    &UndirectedTemporalNet::edges_cause)
      .def("edges_effect",   &UndirectedTemporalNet::edges_effect)
      .def("incident_edges", &UndirectedTemporalNet::incident_edges, "vert"_a)
      .def("in_degree",      &UndirectedTemporalNet::in_degree, "vert"_a)
      .def("out_degree",     &UndirectedTemporalNet::out_degree, "vert"_a)
      .def("degree",         &UndirectedTemporalNet::degree, "vert"_a)
      .def("predecessors",   &UndirectedTemporalNet::predecessors, "vert"_a)
      .def("successors",     &UndirectedTemporalNet::successors, "vert"_a)
      .def("neighbours",     &UndirectedTemporalNet::neighbours, "vert"_a)
      .def("in_edges",
          py::overload_cast<const VertT&>(
            &UndirectedTemporalNet::in_edges, py::const_), "vert"_a)
      .def("out_edges",
          py::overload_cast<const VertT&>(
            &UndirectedTemporalNet::out_edges, py::const_), "vert"_a)
      .def("in_edges",
          py::overload_cast<>(&UndirectedTemporalNet::in_edges, py::const_))
      .def("out_edges",
          py::overload_cast<>(&UndirectedTemporalNet::out_edges, py::const_))
      .def("__repr__", [](const UndirectedTemporalNet& a) {
        return fmt::format("{}", a);
      });

    using DirectedTemporalNet = dag::directed_temporal_network<VertT, TimeT>;
    py::class_<DirectedTemporalNet>(m,
        type_str<DirectedTemporalNet>{}().c_str())
      .def(py::init<std::vector<typename DirectedTemporalNet::EdgeType>>(),
          "edges"_a)
      .def(py::init<
            std::vector<typename DirectedTemporalNet::EdgeType>,
            std::vector<VertT>>(),
          "edges"_a, "verts"_a)
      .def("vertices",       &DirectedTemporalNet::vertices)
      .def("edges",          &DirectedTemporalNet::edges)
      .def("edges_cause",    &DirectedTemporalNet::edges_cause)
      .def("edges_effect",   &DirectedTemporalNet::edges_effect)
      .def("incident_edges", &DirectedTemporalNet::incident_edges, "vert"_a)
      .def("in_degree",      &DirectedTemporalNet::in_degree, "vert"_a)
      .def("out_degree",     &DirectedTemporalNet::out_degree, "vert"_a)
      .def("degree",         &DirectedTemporalNet::degree, "vert"_a)
      .def("predecessors",   &DirectedTemporalNet::predecessors, "vert"_a)
      .def("successors",     &DirectedTemporalNet::successors, "vert"_a)
      .def("neighbours",     &DirectedTemporalNet::neighbours, "vert"_a)
      .def("in_edges",
          py::overload_cast<const VertT&>(
            &DirectedTemporalNet::in_edges, py::const_), "vert"_a)
      .def("out_edges",
          py::overload_cast<const VertT&>(
            &DirectedTemporalNet::out_edges, py::const_), "vert"_a)
      .def("in_edges",
          py::overload_cast<>(&DirectedTemporalNet::in_edges, py::const_))
      .def("out_edges",
          py::overload_cast<>(&DirectedTemporalNet::out_edges, py::const_))
      .def("__repr__", [](const DirectedTemporalNet& a) {
        return fmt::format("{}", a);
      });

    using DelayedTemporalNet =
      dag::directed_delayed_temporal_network<VertT, TimeT>;
    py::class_<DelayedTemporalNet>(m,
        type_str<DelayedTemporalNet>{}().c_str())
      .def(py::init<std::vector<typename DelayedTemporalNet::EdgeType>>(),
          "edges"_a)
      .def(py::init<
            std::vector<typename DelayedTemporalNet::EdgeType>,
            std::vector<VertT>>(),
          "edges"_a, "verts"_a)
      .def("vertices",       &DelayedTemporalNet::vertices)
      .def("edges",          &DelayedTemporalNet::edges)
      .def("edges_cause",    &DelayedTemporalNet::edges_cause)
      .def("edges_effect",   &DelayedTemporalNet::edges_effect)
      .def("incident_edges", &DelayedTemporalNet::incident_edges, "vert"_a)
      .def("in_degree",      &DelayedTemporalNet::in_degree, "vert"_a)
      .def("out_degree",     &DelayedTemporalNet::out_degree, "vert"_a)
      .def("degree",         &DelayedTemporalNet::degree, "vert"_a)
      .def("predecessors",   &DelayedTemporalNet::predecessors, "vert"_a)
      .def("successors",     &DelayedTemporalNet::successors, "vert"_a)
      .def("neighbours",     &DelayedTemporalNet::neighbours, "vert"_a)
      .def("in_edges",
          py::overload_cast<const VertT&>(
            &DelayedTemporalNet::in_edges, py::const_), "vert"_a)
      .def("out_edges",
          py::overload_cast<const VertT&>(
            &DelayedTemporalNet::out_edges, py::const_), "vert"_a)
      .def("in_edges",
          py::overload_cast<>(&DelayedTemporalNet::in_edges, py::const_))
      .def("out_edges",
          py::overload_cast<>(&DelayedTemporalNet::out_edges, py::const_))
      .def("__repr__", [](const DelayedTemporalNet& a) {
        return fmt::format("{}", a);
      });
  }
};

void declare_typed_temporal_networks(py::module& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_networks>>,
      metal::cartesian<types::first_order_vert_types, types::time_types>
    >>{}(m);
}
