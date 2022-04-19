#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <dag/algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <dag::static_undirected_edge EdgeT>
struct declare_undirected_network_algorithms {
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
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, dag::component<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("graph_union",
        &dag::graph_union<EdgeT>,
        "g1"_a, "g2"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_edges",
        &dag::with_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_edges",
        &dag::edge_induced_subgraph<
          EdgeT, dag::component<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_vertices",
        &dag::with_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_vertices",
        &dag::vertex_induced_subgraph<
          EdgeT, dag::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("connected_component",
        &dag::connected_component<EdgeT>,
        "undirected_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("is_connected",
        &dag::is_connected<EdgeT>,
        "undirected_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("connected_components",
        &dag::connected_components<EdgeT>,
        "undirected_network"_a, "singletons"_a = true,
        py::call_guard<py::gil_scoped_release>());

    m.def("is_reachable",
        &dag::is_reachable<EdgeT>,
        "undirected_network"_a, "source"_a, "destination"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

template <dag::static_undirected_edge EdgeT>
struct declare_undirected_density_algorithm {
  void operator()(py::module& m) {
    m.def("density",
        py::overload_cast<const dag::network<EdgeT>&>(
          &dag::density<typename EdgeT::VertexType>),
        "undirected_network"_a);
  }
};

void declare_typed_undirected_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_undirected_network_algorithms>,
      metal::join<
        types::first_order_undirected_edges,
        types::first_order_undirected_hyperedges,
        types::second_order_undirected_edges>>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_undirected_density_algorithm>,
      metal::join<
        types::first_order_undirected_edges,
        types::second_order_undirected_edges>>>{}(m);
}
