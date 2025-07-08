#include "../bind_core.hpp"

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::undirected_network_edge EdgeT>
struct declare_undirected_edge_degree_algorithms {
  void operator()(nb::module_& m) {
    m.def("edge_degree",
          &reticula::edge_degree<EdgeT>,
          "edge"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("edge_degree_sequence",
          &reticula::edge_degree_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
  }
};

template <reticula::network_edge EdgeT>
struct declare_edge_degree_algorithms {
  void operator()(nb::module_& m) {
    m.def("edge_in_degree",
          &reticula::edge_in_degree<EdgeT>,
          "edge"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("edge_out_degree",
          &reticula::edge_out_degree<EdgeT>,
          "edge"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("edge_incident_degree",
          &reticula::edge_incident_degree<EdgeT>,
          "edge"_a,
          nb::call_guard<nb::gil_scoped_release>());

    m.def("edge_in_degree_sequence",
          &reticula::edge_in_degree_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("edge_out_degree_sequence",
          &reticula::edge_out_degree_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("edge_incident_degree_sequence",
          &reticula::edge_incident_degree_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("edge_in_out_degree_pair_sequence",
          &reticula::edge_in_out_degree_pair_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
  }
};
}

void declare_typed_edge_degree_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_undirected_edge_degree_algorithms>,
      metal::join<
        types::first_order_undirected_edges,
        types::second_order_undirected_edges,
        types::first_order_undirected_hyperedges,
        types::first_order_undirected_temporal_edges,
        types::first_order_undirected_temporal_hyperedges>>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_edge_degree_algorithms>,
      types::all_edge_types>>{}(m);
}
