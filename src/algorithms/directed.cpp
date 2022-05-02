#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/stl.h>

#include <dag/algorithms.hpp>

#include "../type_utils.hpp"

namespace py = nanobind;
using namespace nanobind::literals;

namespace nanobind {
    namespace detail {
        template <dag::network_vertex VertT>
        class type_caster<std::vector<dag::component<VertT>>>
            : public type_caster_base<
              std::vector<dag::component<VertT>>> {};
        template <dag::network_vertex VertT>
        class type_caster<std::vector<std::pair<VertT, dag::component<VertT>>>>
            : public type_caster_base<
              std::vector<
                  std::pair<VertT, dag::component<VertT>>>> {};

        template <dag::network_vertex VertT>
        class type_caster<std::vector<dag::component_size<VertT>>>
            : public type_caster_base<
              std::vector<dag::component_size<VertT>>> {};
        template <dag::network_vertex VertT>
        class type_caster<
            std::vector<std::pair<VertT, dag::component_size<VertT>>>>
            : public type_caster_base<
            std::vector<
                std::pair<VertT, dag::component_size<VertT>>>> {};

        template <dag::network_vertex VertT>
        class type_caster<std::vector<dag::component_size_estimate<VertT>>>
            : public type_caster_base<
              std::vector<dag::component_size_estimate<VertT>>> {};
        template <dag::network_vertex VertT>
        class type_caster<
            std::vector<std::pair<VertT, dag::component_size_estimate<VertT>>>>
            : public type_caster_base<
              std::vector<
                  std::pair<VertT, dag::component_size_estimate<VertT>>>> {};
    }
}

template <dag::static_directed_edge EdgeT>
struct declare_directed_network_algorithms {
  void operator()(nb::module& m) {
    m.def("vertex_induced_subgraph",
        &dag::vertex_induced_subgraph<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("vertex_induced_subgraph",
        &dag::vertex_induced_subgraph<
          EdgeT, dag::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, dag::component<EdgeT>>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("graph_union",
        &dag::graph_union<EdgeT>,
        "g1"_a, "g2"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("with_edges",
        &dag::with_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("with_edges",
        &dag::edge_induced_subgraph<
          EdgeT, dag::component<EdgeT>>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("with_vertices",
        &dag::with_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("with_vertices",
        &dag::vertex_induced_subgraph<
          EdgeT, dag::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("is_acyclic",
        &dag::is_acyclic<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("topological_order",
        &dag::topological_order<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("out_component",
        &dag::out_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_components",
        &dag::out_components<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_component_sizes",
        &dag::out_component_sizes<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_component_size_estimates",
        &dag::out_component_size_estimates<EdgeT>,
        "directed_network"_a, "seed"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("in_component",
        &dag::in_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_components",
        &dag::in_components<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_component_sizes",
        &dag::in_component_sizes<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_component_size_estimates",
        &dag::in_component_size_estimates<EdgeT>,
        "directed_network"_a, "seed"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("weakly_connected_component",
        &dag::weakly_connected_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("is_weakly_connected",
        &dag::is_weakly_connected<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("weakly_connected_components",
        &dag::weakly_connected_components<EdgeT>,
        "directed_network"_a, "singletons"_a = true,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("is_reachable",
        &dag::is_reachable<EdgeT>,
        "directed_network"_a, "source"_a, "destination"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

template <dag::static_directed_edge EdgeT>
struct declare_directed_density_algorithm {
  void operator()(nb::module& m) {
    m.def("density",
        nb::overload_cast<const dag::network<EdgeT>&>(
            &dag::density<typename EdgeT::VertexType>),
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};


void declare_typed_directed_algorithms(nb::module& m) {
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
