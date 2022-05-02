#include <nanobind/nanobind.h>

#include <dag/microcanonical_reference_models.hpp>

#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <dag::temporal_edge EdgeT, std::uniform_random_bit_generator Gen>
struct declare_mrrm_algorithms {
  void operator()(nb::module& m) {
    m.def("instant_event_shuffling",
        &dag::mrrms::instant_event_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("link_shuffling",
        &dag::mrrms::link_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("connected_link_shuffling",
        &dag::mrrms::connected_link_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("topology_constrained_link_shuffling",
        &dag::mrrms::topology_constrained_link_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("timeline_shuffling",
        nb::overload_cast<
                const dag::network<EdgeT>&, Gen&,
                typename EdgeT::TimeType, typename EdgeT::TimeType>(
            &dag::mrrms::timeline_shuffling<EdgeT, Gen>),
        "temporal_network"_a, "random_state"_a, "t_start"_a, "t_end"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("timeline_shuffling",
        nb::overload_cast<const dag::network<EdgeT>&, Gen&>(
            &dag::mrrms::timeline_shuffling<EdgeT, Gen>),
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("weight_constrained_timeline_shuffling",
        nb::overload_cast<
            const dag::network<EdgeT>&, Gen&,
            typename EdgeT::TimeType, typename EdgeT::TimeType>(
          &dag::mrrms::weight_constrained_timeline_shuffling<EdgeT, Gen>),
        "temporal_network"_a, "random_state"_a, "t_start"_a, "t_end"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("weight_constrained_timeline_shuffling",
        nb::overload_cast<const dag::network<EdgeT>&, Gen&>(
          &dag::mrrms::weight_constrained_timeline_shuffling<EdgeT, Gen>),
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("activity_constrained_timeline_shuffling",
        &dag::mrrms::activity_constrained_timeline_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("inter_event_shuffling",
        &dag::mrrms::inter_event_shuffling<EdgeT, Gen>,
        "temporal_network"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_mrrm_algorithms(nb::module& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_mrrm_algorithms>>,
      metal::cartesian<
        metal::join<
          types::first_order_undirected_temporal_edges,
          types::first_order_directed_temporal_edges,
          types::first_order_directed_delayed_temporal_edges>,
        types::random_state_types>>>{}(m);
}
