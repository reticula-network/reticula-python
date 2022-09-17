#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>
#include <reticula/temporal_algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::temporal_edge EdgeT>
struct declare_temporal_network_algorithms {
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
  }
};

template <reticula::temporal_adjacency::temporal_adjacency AdjT>
struct declare_temporal_network_adjacency_algorithms {
  void operator()(py::module& m) {
    using EdgeT = AdjT::EdgeType;
    m.def("event_graph",
        &reticula::event_graph<EdgeT, AdjT>,
        "temporal_network"_a, "adjacency"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("make_implicit_event_graph",
        [](const std::vector<EdgeT>& events, const AdjT& adj) {
          return reticula::implicit_event_graph<EdgeT, AdjT>(events, adj);
        }, "events"_a, "adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("make_implicit_event_graph",
        [](const reticula::network<EdgeT>& temp, const AdjT& adj) {
          return reticula::implicit_event_graph<EdgeT, AdjT>(
              temp.edges_cause(), adj);
        }, "temporal_network"_a, "adjacency"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("is_reachable",
        &reticula::is_reachable<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        "source"_a, "t0"_a, "destination"_a, "t1"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_cluster",
        py::overload_cast<
          const reticula::network<EdgeT>&,
          const AdjT&,
          const typename EdgeT::VertexType&,
          typename EdgeT::TimeType>(
            &reticula::out_cluster<EdgeT, AdjT>),
        "temporal_network"_a, "temporal_adjacency"_a,
        "vertex"_a, "time"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_cluster",
        py::overload_cast<
          const reticula::network<EdgeT>&,
          const AdjT&,
          const EdgeT&>(
            &reticula::out_cluster<EdgeT, AdjT>),
        "temporal_network"_a, "temporal_adjacency"_a,
        "event"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_clusters",
        &reticula::out_clusters<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_cluster_sizes",
        &reticula::out_cluster_sizes<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_cluster_size_estimates",
        &reticula::out_cluster_size_estimates<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        "time_resolution"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());


    m.def("in_cluster",
        py::overload_cast<
          const reticula::network<EdgeT>&,
          const AdjT&,
          const typename EdgeT::VertexType&,
          typename EdgeT::TimeType>(
            &reticula::in_cluster<EdgeT, AdjT>),
        "temporal_network"_a, "temporal_adjacency"_a,
        "vertex"_a, "time"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("in_cluster",
        py::overload_cast<
          const reticula::network<EdgeT>&,
          const AdjT&,
          const EdgeT&>(
            &reticula::in_cluster<EdgeT, AdjT>),
        "temporal_network"_a, "temporal_adjacency"_a,
        "event"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("in_clusters",
        &reticula::in_clusters<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_cluster_sizes",
        &reticula::in_cluster_sizes<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_cluster_size_estimates",
        &reticula::in_cluster_size_estimates<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        "time_resolution"_a, "seed"_a,
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

void declare_typed_temporal_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_network_algorithms>,
      metal::join<
        types::first_order_temporal_edges>>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_network_adjacency_algorithms>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
