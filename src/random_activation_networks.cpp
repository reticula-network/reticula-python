#include "bind_core.hpp"

#include <reticula/distributions.hpp>
#include <reticula/random_networks.hpp>

#include "type_str/scalars.hpp"
#include "type_str/distributions.hpp"
#include "type_utils.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <
  reticula::temporal_network_edge EdgeT,
  reticula::random_number_distribution Dist,
  reticula::random_number_distribution ResDist,
  std::uniform_random_bit_generator Gen>
struct declare_activations_with_residual {
  void operator()(nb::module_& m) {
    m.def("random_link_activation_temporal_network",
        &reticula::random_link_activation_temporal_network<
          EdgeT, Dist, ResDist, Gen>,
        "base_net"_a, "max_t"_a, "iet_dist"_a, "res_dist"_a,
        "random_state"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("random_node_activation_temporal_network",
        &reticula::random_node_activation_temporal_network<
          EdgeT, Dist, ResDist, Gen>,
        "base_net"_a, "max_t"_a, "iet_dist"_a, "res_dist"_a,
        "random_state"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

template <
  reticula::temporal_network_edge EdgeT,
  reticula::random_number_distribution Dist,
  std::uniform_random_bit_generator Gen>
struct declare_activations {
  void operator()(nb::module_& m) {
    m.def("random_link_activation_temporal_network",
        &reticula::random_link_activation_temporal_network<
          EdgeT, Dist, Gen>,
        "base_net"_a, "max_t"_a, "iet_dist"_a,
        "random_state"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("random_node_activation_temporal_network",
        &reticula::random_node_activation_temporal_network<
          EdgeT, Dist, Gen>,
        "base_net"_a, "max_t"_a, "iet_dist"_a,
        "random_state"_a, "size_hint"_a = 0,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

template <typename TimeType>
struct type_dists {};

template <std::integral TimeType>
struct type_dists<TimeType> {
  using list = metal::list<
    std::geometric_distribution<TimeType>,
    reticula::delta_distribution<TimeType>,
    std::uniform_int_distribution<TimeType>>;
};

template <std::floating_point TimeType>
struct type_dists<TimeType> {
  using list = metal::list<
    std::exponential_distribution<TimeType>,
    reticula::power_law_with_specified_mean<TimeType>,
    reticula::residual_power_law_with_specified_mean<TimeType>,
    reticula::hawkes_univariate_exponential<TimeType>,
    reticula::delta_distribution<TimeType>,
    std::uniform_real_distribution<TimeType>>;
};

template <reticula::temporal_network_edge EdgeT>
struct declare_typed_activations_for_edge {
  void operator()(nb::module_& m) {
    using time_type = typename EdgeT::TimeType;
    using dists = typename type_dists<time_type>::list;

    types::run_each<
      metal::transform<
        metal::partial<
          metal::lambda<metal::apply>,
          metal::lambda<declare_activations>>,
        metal::cartesian<
          metal::list<EdgeT>,
          dists,
          types::random_state_types>>>{}(m);

    types::run_each<
      metal::transform<
        metal::partial<
          metal::lambda<metal::apply>,
          metal::lambda<declare_activations_with_residual>>,
        metal::cartesian<
          metal::list<EdgeT>,
          dists, dists,
          types::random_state_types>>>{}(m);
  }
};
}

void declare_typed_activation_networks(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_typed_activations_for_edge>,
      metal::join<
        types::first_order_undirected_temporal_edges,
        types::first_order_undirected_temporal_hyperedges,
        types::first_order_directed_temporal_edges,
        types::first_order_directed_temporal_hyperedges>>>{}(m);
}
