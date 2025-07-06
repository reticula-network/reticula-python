#include "../bind_core.hpp"

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::undirected_network_edge EdgeT>
struct declare_undirected_degree_algorithms {
  void operator()(nb::module_& m) {
    m.def("degree",
          &reticula::degree<EdgeT>,
          "network"_a,
          "vertex"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("degree_sequence",
          &reticula::degree_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
  }
};

template <reticula::network_edge EdgeT>
struct declare_degree_algorithms {
  void operator()(nb::module_& m) {
    m.def("in_degree",
          &reticula::in_degree<EdgeT>,
          "network"_a,
          "vertex"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("out_degree",
          &reticula::out_degree<EdgeT>,
          "network"_a,
          "vertex"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("incident_degree",
          &reticula::incident_degree<EdgeT>,
          "network"_a,
          "vertex"_a,
          nb::call_guard<nb::gil_scoped_release>());

    m.def("in_degree_sequence",
          &reticula::in_degree_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("out_degree_sequence",
          &reticula::out_degree_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("incident_degree_sequence",
          &reticula::incident_degree_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("in_out_degree_pair_sequence",
          &reticula::in_out_degree_pair_sequence<EdgeT>,
          "network"_a,
          nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_degree_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_undirected_degree_algorithms>,
      metal::join<
        types::first_order_undirected_edges,
        types::second_order_undirected_edges,
        types::first_order_undirected_hyperedges,
        types::first_order_undirected_temporal_edges,
        types::first_order_undirected_temporal_hyperedges>>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_degree_algorithms>,
      types::all_edge_types>>{}(m);
}
