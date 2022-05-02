#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/stl.h>

#include <dag/implicit_event_graph.hpp>
#include <dag/implicit_event_graph_components.hpp>

#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <dag::temporal_adjacency::temporal_adjacency AdjT>
struct declare_implicit_event_graph_component_algorithms {
  void operator()(nb::module& m) {
    using EdgeT = AdjT::EdgeType;
    m.def("out_component",
        &dag::out_component<EdgeT, AdjT>,
        "implicit_event_graph"_a, "root"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_components",
        &dag::out_components<EdgeT, AdjT>,
        "implicit_event_graph"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_component_sizes",
        &dag::out_component_sizes<EdgeT, AdjT>,
        "implicit_event_graph"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("out_component_size_estimates",
        &dag::out_component_size_estimates<EdgeT, AdjT>,
        "implicit_event_graph"_a, "seed"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("in_component",
        &dag::in_component<EdgeT, AdjT>,
        "implicit_event_graph"_a, "root"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_components",
        &dag::in_components<EdgeT, AdjT>,
        "implicit_event_graph"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_component_sizes",
        &dag::in_component_sizes<EdgeT, AdjT>,
        "implicit_event_graph"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("in_component_size_estimates",
        &dag::in_component_size_estimates<EdgeT, AdjT>,
        "implicit_event_graph"_a, "seed"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("weakly_connected_component",
        &dag::weakly_connected_component<EdgeT, AdjT>,
        "implicit_event_graph"_a, "root"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("weakly_connected_components",
        &dag::weakly_connected_components<EdgeT, AdjT>,
        "implicit_event_graph"_a, "singletons"_a = true,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_implicit_event_graph_components(nb::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_implicit_event_graph_component_algorithms>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
