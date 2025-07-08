#include "bind_core.hpp"

#include <reticula/random_networks.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <
  reticula::integer_network_vertex VertT,
  std::uniform_random_bit_generator Gen>
struct declare_random_network_models {
  void operator()(nb::module_& m) {
    m.def(("random_gnp_graph_"+python_type_str<VertT>()).c_str(),
        &reticula::random_gnp_graph<VertT, Gen>,
        "n"_a, "p"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def(("random_directed_gnp_graph_"+python_type_str<VertT>()).c_str(),
        &reticula::random_directed_gnp_graph<VertT, Gen>,
        "n"_a, "p"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());


    m.def(("random_barabasi_albert_graph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_barabasi_albert_graph<VertT, Gen>,
        "n"_a, "m"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def(("random_regular_graph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_regular_graph<VertT, Gen>,
        "size"_a, "degree"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());


    m.def(("random_expected_degree_sequence_graph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_expected_degree_sequence_graph<
          VertT, std::vector<double>, Gen>,
        "weight_sequence"_a, "random_state"_a, "self_loops"_a = false,
        nb::call_guard<nb::gil_scoped_release>());

    m.def(("random_directed_expected_degree_sequence_graph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_directed_expected_degree_sequence_graph<
          VertT, std::vector<std::pair<double, double>>, Gen>,
        "in_out_weight_sequence"_a, "random_state"_a, "self_loops"_a = false,
        nb::call_guard<nb::gil_scoped_release>());


    m.def(("random_expected_degree_sequence_hypergraph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_expected_degree_sequence_hypergraph<
          VertT, std::vector<double>, std::vector<double>, Gen>,
        "vertex_weight_sequence"_a, "edge_weight_sequence"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def(("random_directed_expected_degree_sequence_hypergraph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_directed_expected_degree_sequence_hypergraph<
          VertT, std::vector<std::pair<double, double>>,
          std::vector<std::pair<double, double>>, Gen>,
        "vertex_in_out_weight_sequence"_a, "edge_in_out_weight_sequence"_a,
        "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());


    m.def(("random_uniform_hypergraph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_uniform_hypergraph<VertT, Gen>,
        "size"_a, "edge_degree"_a, "edge_prob"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def(("random_directed_uniform_hypergraph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_directed_uniform_hypergraph<VertT, Gen>,
        "size"_a, "edge_in_degree"_a, "edge_out_degree"_a, "edge_prob"_a,
        "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());


    m.def(("random_degree_sequence_graph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_degree_sequence_graph<
          VertT, std::vector<VertT>, Gen>,
        "degree_sequence"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def(("random_directed_degree_sequence_graph_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_directed_degree_sequence_graph<
          VertT, std::vector<std::pair<VertT, VertT>>, Gen>,
        "in_out_degree_sequence"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());


    m.def(("random_fully_mixed_temporal_network_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_fully_mixed_temporal_network<VertT, Gen>,
        "size"_a, "rate"_a, "max_t"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def(("random_directed_fully_mixed_temporal_network_"+
          python_type_str<VertT>()).c_str(),
        &reticula::random_directed_fully_mixed_temporal_network<VertT, Gen>,
        "size"_a, "rate"_a, "max_t"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};
}

void declare_typed_random_networks(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_random_network_models>>,
      metal::cartesian<
        types::integer_vert_types,
        types::random_state_types>>>{}(m);
}
