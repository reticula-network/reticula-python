#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <dag/algorithms.hpp>
#include <dag/temporal_algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

namespace pybind11 {
    namespace detail {
        template <
            dag::temporal_edge EdgeT,
            dag::temporal_adjacency::temporal_adjacency AdjT>
        class type_caster<std::vector<
            std::pair<EdgeT, dag::temporal_cluster<EdgeT, AdjT>>>>
            : public type_caster_base<std::vector<
                std::pair<EdgeT,
                    dag::temporal_cluster<EdgeT, AdjT>>>> {};

        template <
            dag::temporal_edge EdgeT,
            dag::temporal_adjacency::temporal_adjacency AdjT>
        class type_caster<std::vector<
            std::pair<EdgeT, dag::temporal_cluster_size<EdgeT, AdjT>>>>
            : public type_caster_base<std::vector<
                std::pair<EdgeT,
                    dag::temporal_cluster_size<EdgeT, AdjT>>>> {};
        template <
            dag::temporal_edge EdgeT,
            dag::temporal_adjacency::temporal_adjacency AdjT>
        class type_caster<std::vector<
            std::pair<EdgeT, dag::temporal_cluster_size_estimate<EdgeT, AdjT>>>>
            : public type_caster_base<std::vector<
                std::pair<EdgeT,
                    dag::temporal_cluster_size_estimate<EdgeT, AdjT>>>> {};
    }
}

template <dag::temporal_edge EdgeT>
struct declare_temporal_network_algorithms {
  void operator()(py::module& m) {
    m.def("vertex_induced_subgraph",
        &dag::vertex_induced_subgraph<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("vertex_induced_subgraph",
        &dag::vertex_induced_subgraph<
          EdgeT, dag::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("edge_induced_subgraph",
        &dag::edge_induced_subgraph<
          EdgeT, dag::component<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("graph_union",
        &dag::graph_union<EdgeT>,
        "g1"_a, "g2"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_edges",
        &dag::with_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_edges",
        &dag::edge_induced_subgraph<
          EdgeT, dag::component<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_vertices",
        &dag::with_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_vertices",
        &dag::vertex_induced_subgraph<
          EdgeT, dag::component<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("time_window",
        &dag::time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("cause_time_window",
        &dag::cause_time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("effect_time_window",
        &dag::effect_time_window<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

template <dag::temporal_adjacency::temporal_adjacency AdjT>
struct declare_temporal_network_adjacency_algorithms {
  void operator()(py::module& m) {
    using EdgeT = AdjT::EdgeType;
    m.def("event_graph",
        &dag::event_graph<EdgeT, AdjT>,
        "temporal_network"_a, "adjacency"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("is_reachable",
        &dag::is_reachable<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        "source"_a, "t0"_a, "destination"_a, "t1"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_cluster",
        py::overload_cast<
          const dag::network<EdgeT>&,
          const AdjT&,
          const typename EdgeT::VertexType&,
          typename EdgeT::TimeType>(
            &dag::out_cluster<EdgeT, AdjT>),
        "temporal_network"_a, "temporal_adjacency"_a,
        "vertex"_a, "time"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_cluster",
        py::overload_cast<
          const dag::network<EdgeT>&,
          const AdjT&,
          const EdgeT&>(
            &dag::out_cluster<EdgeT, AdjT>),
        "temporal_network"_a, "temporal_adjacency"_a,
        "event"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_clusters",
        &dag::out_clusters<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_cluster_sizes",
        &dag::out_cluster_sizes<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_cluster_size_estimates",
        &dag::out_cluster_size_estimates<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        "time_resolution"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());


    m.def("in_cluster",
        py::overload_cast<
          const dag::network<EdgeT>&,
          const AdjT&,
          const typename EdgeT::VertexType&,
          typename EdgeT::TimeType>(
            &dag::in_cluster<EdgeT, AdjT>),
        "temporal_network"_a, "temporal_adjacency"_a,
        "vertex"_a, "time"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("in_cluster",
        py::overload_cast<
          const dag::network<EdgeT>&,
          const AdjT&,
          const EdgeT&>(
            &dag::in_cluster<EdgeT, AdjT>),
        "temporal_network"_a, "temporal_adjacency"_a,
        "event"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("in_clusters",
        &dag::in_clusters<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_cluster_sizes",
        &dag::in_cluster_sizes<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_cluster_size_estimates",
        &dag::in_cluster_size_estimates<EdgeT, AdjT>,
        "temporal_network"_a, "temporal_adjacency"_a,
        "time_resolution"_a, "seed"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("static_projection",
        &dag::static_projection<EdgeT>,
        "temporal_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("link_timeline",
        &dag::link_timeline<EdgeT>,
        "temporal_network"_a, "static_link"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("link_timelines",
        &dag::link_timelines<EdgeT>,
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
