#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <dag/algorithms.hpp>

#include "../type_str.hpp"
#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <dag::static_directed_edge EdgeT>
struct declare_directed_network_algorithms {
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

    m.def("is_acyclic",
        &dag::is_acyclic<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("topological_order",
        &dag::topological_order<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_component",
        &dag::out_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_components",
        &dag::out_components<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_component_sizes",
        &dag::out_component_sizes<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_component_size_estimates",
        &dag::out_component_size_estimates<EdgeT>,
        "directed_network"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("in_component",
        &dag::in_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_components",
        &dag::in_components<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_component_sizes",
        &dag::in_component_sizes<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_component_size_estimates",
        &dag::in_component_size_estimates<EdgeT>,
        "directed_network"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("weakly_connected_component",
        &dag::weakly_connected_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("is_weakly_connected",
        &dag::is_weakly_connected<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("weakly_connected_components",
        &dag::weakly_connected_components<EdgeT>,
        "directed_network"_a, "singletons"_a = true,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_directed_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_directed_network_algorithms>,
      metal::join<
        types::first_order_directed_edges,
        types::first_order_directed_hyperedges,
        types::second_order_directed_edges>>>{}(m);
}
