#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <dag/algorithms.hpp>

#include "../type_str.hpp"
#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <dag::static_undirected_edge EdgeT>
struct declare_undirected_network_algorithms {
  void operator()(py::module& m) {
    m.def("vertex_induced_subgraph",
        &dag::vertex_induced_subgraph<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a);
    m.def("vertex_induced_subgraph",
        &dag::vertex_induced_subgraph<
          EdgeT, dag::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a);

    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "verts"_a);
    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, dag::component<EdgeT>>,
        "network"_a, "verts"_a);

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
}
