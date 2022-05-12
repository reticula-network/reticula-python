#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

namespace pybind11 {
    namespace detail {
        template <reticula::network_vertex VertT>
        class type_caster<std::vector<reticula::component<VertT>>>
            : public type_caster_base<
              std::vector<reticula::component<VertT>>> {};
        template <reticula::network_vertex VertT>
        class type_caster<std::vector<std::pair<VertT, reticula::component<VertT>>>>
            : public type_caster_base<
              std::vector<
                  std::pair<VertT, reticula::component<VertT>>>> {};

        template <reticula::network_vertex VertT>
        class type_caster<std::vector<reticula::component_size<VertT>>>
            : public type_caster_base<
              std::vector<reticula::component_size<VertT>>> {};
        template <reticula::network_vertex VertT>
        class type_caster<
            std::vector<std::pair<VertT, reticula::component_size<VertT>>>>
            : public type_caster_base<
            std::vector<
                std::pair<VertT, reticula::component_size<VertT>>>> {};

        template <reticula::network_vertex VertT>
        class type_caster<std::vector<reticula::component_size_estimate<VertT>>>
            : public type_caster_base<
              std::vector<reticula::component_size_estimate<VertT>>> {};
        template <reticula::network_vertex VertT>
        class type_caster<
            std::vector<std::pair<VertT, reticula::component_size_estimate<VertT>>>>
            : public type_caster_base<
              std::vector<
                  std::pair<VertT, reticula::component_size_estimate<VertT>>>> {};
    }
}

template <reticula::static_directed_edge EdgeT>
struct declare_directed_network_algorithms {
  void operator()(py::module& m) {
    m.def("vertex_induced_subgraph",
        &reticula::vertex_induced_subgraph<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("vertex_induced_subgraph",
        &reticula::vertex_induced_subgraph<
          EdgeT, reticula::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("edge_induced_subgraph",
        &reticula::edge_induced_subgraph<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("edge_induced_subgraph",
        &reticula::edge_induced_subgraph<
          EdgeT, reticula::component<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("graph_union",
        &reticula::graph_union<EdgeT>,
        "g1"_a, "g2"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_edges",
        &reticula::with_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_edges",
        &reticula::edge_induced_subgraph<
          EdgeT, reticula::component<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_vertices",
        &reticula::with_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_vertices",
        &reticula::vertex_induced_subgraph<
          EdgeT, reticula::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("is_acyclic",
        &reticula::is_acyclic<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("topological_order",
        &reticula::topological_order<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_component",
        &reticula::out_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_components",
        &reticula::out_components<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_component_sizes",
        &reticula::out_component_sizes<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_component_size_estimates",
        &reticula::out_component_size_estimates<EdgeT>,
        "directed_network"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("in_component",
        &reticula::in_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_components",
        &reticula::in_components<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_component_sizes",
        &reticula::in_component_sizes<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_component_size_estimates",
        &reticula::in_component_size_estimates<EdgeT>,
        "directed_network"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("weakly_connected_component",
        &reticula::weakly_connected_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("is_weakly_connected",
        &reticula::is_weakly_connected<EdgeT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("weakly_connected_components",
        &reticula::weakly_connected_components<EdgeT>,
        "directed_network"_a, "singletons"_a = true,
        py::call_guard<py::gil_scoped_release>());

    m.def("is_reachable",
        &reticula::is_reachable<EdgeT>,
        "directed_network"_a, "source"_a, "destination"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("shortest_path_lengths_from",
        &reticula::shortest_path_lengths_from<EdgeT>,
        "directed_network"_a, "source"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("shortest_path_lengths_to",
        &reticula::shortest_path_lengths_to<EdgeT>,
        "directed_network"_a, "destination"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

template <reticula::static_directed_edge EdgeT>
struct declare_directed_density_algorithm {
  void operator()(py::module& m) {
    m.def("density",
        py::overload_cast<const reticula::network<EdgeT>&>(
            &reticula::density<typename EdgeT::VertexType>),
        "directed_network"_a,
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

  types::run_each<
    metal::transform<
      metal::lambda<declare_directed_density_algorithm>,
      metal::join<
        types::first_order_directed_edges,
        types::second_order_directed_edges>>>{}(m);
}
