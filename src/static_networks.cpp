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

template <typename VertT>
struct declare_static_networks {
  void operator()(py::module &m) {
    using UndirectedNet = dag::undirected_network<VertT>;
    py::class_<UndirectedNet>(m, type_str<UndirectedNet>{}().c_str())
      .def(py::init<std::vector<typename UndirectedNet::EdgeType>>())
      .def(py::init<std::vector<typename UndirectedNet::EdgeType>,
          std::vector<VertT>>())
      .def("vertices",       &UndirectedNet::vertices)
      .def("edges",          &UndirectedNet::edges)
      .def("edges_cause",    &UndirectedNet::edges_cause)
      .def("edges_effect",   &UndirectedNet::edges_effect)
      .def("incident_edges", &UndirectedNet::incident_edges)
      .def("in_degree",      &UndirectedNet::in_degree)
      .def("out_degree",     &UndirectedNet::out_degree)
      .def("degree",         &UndirectedNet::degree)
      .def("predecessors",   &UndirectedNet::predecessors)
      .def("successors",     &UndirectedNet::successors)
      .def("neighbours",     &UndirectedNet::neighbours)
      .def("in_edges",
          py::overload_cast<const VertT&>(&UndirectedNet::in_edges, py::const_))
      .def("out_edges",
          py::overload_cast<const VertT&>(&UndirectedNet::out_edges, py::const_))
      .def("in_edges",
          py::overload_cast<>(&UndirectedNet::in_edges, py::const_))
      .def("out_edges",
          py::overload_cast<>(&UndirectedNet::out_edges, py::const_))
      .def("__repr__", [](const UndirectedNet& a) {
        return fmt::format("{}", a);
      });

  using DirectedNet = dag::directed_network<VertT>;
  py::class_<DirectedNet>(m, type_str<DirectedNet>{}().c_str())
    .def(py::init<std::vector<typename DirectedNet::EdgeType>>())
    .def(py::init<std::vector<typename DirectedNet::EdgeType>,
        std::vector<VertT>>())
    .def("vertices",       &DirectedNet::vertices)
    .def("edges",          &DirectedNet::edges)
    .def("edges_cause",    &DirectedNet::edges_cause)
    .def("edges_effect",   &DirectedNet::edges_effect)
    .def("incident_edges", &DirectedNet::incident_edges)
    .def("in_degree",      &DirectedNet::in_degree)
    .def("out_degree",     &DirectedNet::out_degree)
    .def("degree",         &DirectedNet::degree)
    .def("predecessors",   &DirectedNet::predecessors)
    .def("successors",     &DirectedNet::successors)
    .def("neighbours",     &DirectedNet::neighbours)
    .def("in_edges",
        py::overload_cast<const VertT&>(&DirectedNet::in_edges, py::const_))
    .def("out_edges",
        py::overload_cast<const VertT&>(&DirectedNet::out_edges, py::const_))
    .def("in_edges",
        py::overload_cast<>(&DirectedNet::in_edges, py::const_))
    .def("out_edges",
        py::overload_cast<>(&DirectedNet::out_edges, py::const_))
    .def("__repr__", [](const DirectedNet& a) {
      return fmt::format("{}", a);
    });
  }
};

void declare_typed_static_networks(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_networks>,
      types::simple_vert_types>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_static_networks>,
      types::simple_temporal_edges>>{}(m);
}
