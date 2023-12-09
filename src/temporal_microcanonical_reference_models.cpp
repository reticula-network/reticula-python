#include "bind_core.hpp"

#include <reticula/microcanonical_reference_models.hpp>

#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <
  reticula::temporal_network_edge EdgeT,
  std::uniform_random_bit_generator Gen>
struct declare_temporal_mrrm_algorithms {
  void operator()(nb::module_& m) {
    m.def("instant_event_shuffling",
        &reticula::mrrms::instant_event_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("link_shuffling",
        &reticula::mrrms::link_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("connected_link_shuffling",
        &reticula::mrrms::connected_link_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("topology_constrained_link_shuffling",
        &reticula::mrrms::topology_constrained_link_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("timeline_shuffling",
        nb::overload_cast<
                const reticula::network<EdgeT>&, Gen&,
                typename EdgeT::TimeType, typename EdgeT::TimeType>(
            &reticula::mrrms::timeline_shuffling<EdgeT, Gen>),
        "temporal_network"_a, "random_state"_a, "t_start"_a, "t_end"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("timeline_shuffling",
        nb::overload_cast<const reticula::network<EdgeT>&, Gen&>(
            &reticula::mrrms::timeline_shuffling<EdgeT, Gen>),
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("weight_constrained_timeline_shuffling",
        nb::overload_cast<
            const reticula::network<EdgeT>&, Gen&,
            typename EdgeT::TimeType, typename EdgeT::TimeType>(
          &reticula::mrrms::weight_constrained_timeline_shuffling<EdgeT, Gen>),
        "temporal_network"_a, "random_state"_a, "t_start"_a, "t_end"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("weight_constrained_timeline_shuffling",
        nb::overload_cast<const reticula::network<EdgeT>&, Gen&>(
          &reticula::mrrms::weight_constrained_timeline_shuffling<EdgeT, Gen>),
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("activity_constrained_timeline_shuffling",
        &reticula::mrrms::activity_constrained_timeline_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("inter_event_shuffling",
        &reticula::mrrms::inter_event_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_temporal_mrrm_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_mrrm_algorithms>>,
      metal::cartesian<
        metal::join<
          types::first_order_undirected_temporal_edges,
          types::first_order_directed_temporal_edges,
          types::first_order_directed_delayed_temporal_edges>,
        types::random_state_types>>>{}(m);
}
