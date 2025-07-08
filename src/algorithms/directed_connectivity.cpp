#include <vector>

#include "../bind_core.hpp"

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::directed_static_network_edge EdgeT>
struct declare_directed_connectivity_algorithms {
  void operator()(nb::module_& m) {
    m.def("is_acyclic",
        &reticula::is_acyclic<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("topological_order",
        &reticula::topological_order<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("out_component",
        &reticula::out_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_components",
        &reticula::out_components<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_component_sizes",
        &reticula::out_component_sizes<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_component_size_estimates",
        &reticula::out_component_size_estimates<EdgeT>,
        "directed_network"_a, "seed"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("in_component",
        &reticula::in_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_components",
        &reticula::in_components<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_component_sizes",
        &reticula::in_component_sizes<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_component_size_estimates",
        &reticula::in_component_size_estimates<EdgeT>,
        "directed_network"_a, "seed"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("weakly_connected_component",
        &reticula::weakly_connected_component<EdgeT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("is_weakly_connected",
        &reticula::is_weakly_connected<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("largest_weakly_connected_component",
        &reticula::largest_weakly_connected_component<EdgeT>,
        "directed_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("weakly_connected_components",
        &reticula::weakly_connected_components<EdgeT>,
        "directed_network"_a, "singletons"_a = true,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("is_reachable",
        &reticula::is_reachable<EdgeT>,
        "network"_a, "source"_a, "destination"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("shortest_path_lengths_from",
        &reticula::shortest_path_lengths_from<EdgeT>,
        "network"_a, "source"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("shortest_path_lengths_to",
        &reticula::shortest_path_lengths_to<EdgeT>,
        "network"_a, "destination"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};
}

void declare_typed_directed_connectivity_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_directed_connectivity_algorithms>,
      metal::join<
        types::first_order_directed_edges,
        types::first_order_directed_hyperedges,
        types::second_order_directed_edges>>>{}(m);
}
