#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <reticula/implicit_event_graphs.hpp>
#include <reticula/implicit_event_graph_components.hpp>

#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::temporal_adjacency::temporal_adjacency AdjT>
struct declare_implicit_event_graph_component_algorithms {
  void operator()(py::module& m) {
    using EdgeT = AdjT::EdgeType;
    m.def("out_component",
        &reticula::out_component<EdgeT, AdjT>,
        "implicit_event_graph"_a, "root"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_components",
        &reticula::out_components<EdgeT, AdjT>,
        "implicit_event_graph"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_component_sizes",
        &reticula::out_component_sizes<EdgeT, AdjT>,
        "implicit_event_graph"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_component_size_estimates",
        &reticula::out_component_size_estimates<EdgeT, AdjT>,
        "implicit_event_graph"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("in_component",
        &reticula::in_component<EdgeT, AdjT>,
        "implicit_event_graph"_a, "root"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_components",
        &reticula::in_components<EdgeT, AdjT>,
        "implicit_event_graph"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_component_sizes",
        &reticula::in_component_sizes<EdgeT, AdjT>,
        "implicit_event_graph"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_component_size_estimates",
        &reticula::in_component_size_estimates<EdgeT, AdjT>,
        "implicit_event_graph"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("weakly_connected_component",
        &reticula::weakly_connected_component<EdgeT, AdjT>,
        "implicit_event_graph"_a, "root"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("weakly_connected_components",
        &reticula::weakly_connected_components<EdgeT, AdjT>,
        "implicit_event_graph"_a, "singletons"_a = true,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_implicit_event_graph_components(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_implicit_event_graph_component_algorithms>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
