#include <vector>

#include "../bind_core.hpp"

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::undirected_static_network_edge EdgeT>
struct declare_undirected_connectivity_algorithms {
  void operator()(nb::module_& m) {
    m.def("connected_component",
        &reticula::connected_component<EdgeT>,
        "undirected_network"_a, "vert"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("is_connected",
        &reticula::is_connected<EdgeT>,
        "undirected_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("largest_connected_component",
        &reticula::largest_connected_component<EdgeT>,
        "undirected_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("connected_components",
        &reticula::connected_components<EdgeT>,
        "undirected_network"_a, "singletons"_a = true,
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

void declare_typed_undirected_connectivity_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_undirected_connectivity_algorithms>,
      metal::join<
        types::first_order_undirected_edges,
        types::first_order_undirected_hyperedges,
        types::second_order_undirected_edges>>>{}(m);
}
