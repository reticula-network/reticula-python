#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <dag/temporal_algorithms.hpp>

#include "../type_str.hpp"
#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <dag::temporal_edge EdgeT>
struct declare_temporal_network_algorithms {
  void operator()(py::module& m) {
    m.def("vertex_induced_subgraph",
        &dag::vertex_induced_subgraph<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("vertex_induced_subgraph",
        &dag::vertex_induced_subgraph<
          EdgeT, dag::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, dag::component<EdgeT>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("graph_union",
        &dag::graph_union<EdgeT>,
        "g1"_a, "g2"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("time_window",
        &dag::time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("cause_time_window",
        &dag::cause_time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("effect_time_window",
        &dag::effect_time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

template <dag::temporal_adjacency::temporal_adjacency AdjT>
struct declare_temporal_network_adjacency_algorithms {
  void operator()(py::module& m) {
    using EdgeT = AdjT::EdgeType;
    m.def("event_graph",
        &dag::event_graph<EdgeT, AdjT>,
        "temporal_network"_a, "adjacency"_a);

    m.def("is_reachable",
        &dag::is_reachable<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        "source"_a, "t0"_a, "destination"_a, "t1"_a);
  }
};

void declare_typed_temporal_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_network_algorithms>,
      metal::join<
        types::first_order_temporal_edges>>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_network_adjacency_algorithms>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
