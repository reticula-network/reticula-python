#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>
#include <reticula/temporal_algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::temporal_network_edge EdgeT>
struct declare_basic_temporal_network_algorithms {
  void operator()(py::module& m) {
    m.def("time_window",
        &reticula::time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("cause_time_window",
        &reticula::cause_time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("effect_time_window",
        &reticula::effect_time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("static_projection",
        &reticula::static_projection<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("link_timeline",
        &reticula::link_timeline<EdgeT>,
        "temporal_network"_a, "static_link"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("link_timelines",
        &reticula::link_timelines<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_basic_temporal_network_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_basic_temporal_network_algorithms>,
      metal::join<
        types::first_order_temporal_edges>>>{}(m);
}
