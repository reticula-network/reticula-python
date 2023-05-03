#include <vector>

#include "../bind_core.hpp"

#include <reticula/algorithms.hpp>
#include <reticula/temporal_algorithms.hpp>

#include "../type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::temporal_network_edge EdgeT>
struct declare_basic_temporal_network_algorithms {
  void operator()(nb::module_& m) {
    m.def("time_window",
        &reticula::time_window<EdgeT>,
        "temporal_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("cause_time_window",
        &reticula::cause_time_window<EdgeT>,
        "temporal_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("effect_time_window",
        &reticula::effect_time_window<EdgeT>,
        "temporal_network"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("static_projection",
        &reticula::static_projection<EdgeT>,
        "temporal_network"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("link_timeline",
        &reticula::link_timeline<EdgeT>,
        "temporal_network"_a, "static_link"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("link_timelines",
        &reticula::link_timelines<EdgeT>,
        "temporal_network"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_basic_temporal_network_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_basic_temporal_network_algorithms>,
      metal::join<
        types::first_order_temporal_edges>>>{}(m);
}
