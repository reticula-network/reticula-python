#include "bind_core.hpp"
#include <nanobind/operators.h>
#include <nanobind/make_iterator.h>

#include <fmt/format.h>
#include <reticula/temporal_clusters.hpp>

#include "type_str/temporal_clusters.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::temporal_adjacency::temporal_adjacency AdjT>
struct declare_temporal_cluster_types {
  void operator()(nb::module_ &m) {
    using EdgeT = typename AdjT::EdgeType;
    using Cluster = reticula::temporal_cluster<EdgeT, AdjT>;
    nb::class_<Cluster>(
        m, python_type_str<Cluster>().c_str())
      .def(nb::init<AdjT, std::size_t>(),
          "temporal_adjacency"_a, "size_hint"_a = 0,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::init<const Cluster&>(),
          "temporal_cluester"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::init<std::vector<EdgeT>, AdjT, std::size_t>(),
          "events"_a,
          "temporal_adjacency"_a,
          "size_hint"_a = 0,
          nb::call_guard<nb::gil_scoped_release>())
      .def("insert",
          static_cast<void (Cluster::*)(
            const EdgeT&)>(
            &Cluster::insert),
          "event"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("insert",
          static_cast<void (Cluster::*)(
            const std::vector<EdgeT>&)>(
            &Cluster::insert),
          "events"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("merge", &Cluster::merge,
          "other"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("covers",
          &Cluster::covers,
          "vertex"_a, "time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("interval_sets",
          &Cluster::interval_sets,
          nb::call_guard<nb::gil_scoped_release>())
      .def("lifetime",
          &Cluster::lifetime,
          nb::call_guard<nb::gil_scoped_release>())
      .def("volume",
          &Cluster::volume,
          nb::call_guard<nb::gil_scoped_release>())
      .def("mass",
          &Cluster::mass,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::self == nb::self,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::self != nb::self,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__len__", &Cluster::size,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__contains__",
          &Cluster::contains,
          "event"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__copy__", [](const Cluster& self) {
          return Cluster(self);
      }).def("__deepcopy__", [](const Cluster& self, nb::dict) {
          return Cluster(self);
      }, "memo"_a)
      .def("__repr__", [](const Cluster& c) {
          return fmt::format("{}", c);
      })
      .def("__iter__", [](const Cluster &c) {
          return nb::make_iterator(nb::type<EdgeT>(), "edge_iterator", c);
      }, nb::keep_alive<0, 1>())
      .def_static("vertex_type", []() {
        return types::handle_for<typename Cluster::VertexType>();
      })
      .def_static("adjacency_type", []() {
        return types::handle_for<typename Cluster::AdjacencyType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<Cluster>{}());
      }).def_static("__class_name__", []() {
        return type_str<Cluster>{}();
      });

    using ClusterSize = reticula::temporal_cluster_size<EdgeT, AdjT>;
    nb::class_<ClusterSize>(
        m, python_type_str<ClusterSize>().c_str())
      .def("lifetime",
          &ClusterSize::lifetime,
          nb::call_guard<nb::gil_scoped_release>())
      .def("volume",
          &ClusterSize::volume,
          nb::call_guard<nb::gil_scoped_release>())
      .def("mass",
          &ClusterSize::mass,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__len__", &ClusterSize::size,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__copy__", [](const ClusterSize& self) {
          return ClusterSize(self);
      }).def("__deepcopy__", [](const ClusterSize& self, nb::dict) {
          return ClusterSize(self);
      }, "memo"_a)
      .def("__repr__", [](const ClusterSize& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename ClusterSize::VertexType>();
      })
      .def_static("adjacency_type", []() {
        return types::handle_for<typename ClusterSize::AdjacencyType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<ClusterSize>{}());
      }).def_static("__class_name__", []() {
        return type_str<ClusterSize>{}();
      });


    using ClusterSizeEstimate =
      reticula::temporal_cluster_size_estimate<EdgeT, AdjT>;
    nb::class_<ClusterSizeEstimate>(
        m, python_type_str<ClusterSizeEstimate>().c_str())
      .def("lifetime",
          &ClusterSizeEstimate::lifetime,
          nb::call_guard<nb::gil_scoped_release>())
      .def("volume_estimate",
          &ClusterSizeEstimate::volume_estimate,
          nb::call_guard<nb::gil_scoped_release>())
      .def("mass_estimate",
          &ClusterSizeEstimate::mass_estimate,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__copy__", [](const ClusterSizeEstimate& self) {
          return ClusterSizeEstimate(self);
      }).def("__deepcopy__", [](const ClusterSizeEstimate& self, nb::dict) {
          return ClusterSizeEstimate(self);
      }, "memo"_a)
      .def("__repr__", [](const ClusterSizeEstimate& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename ClusterSizeEstimate::VertexType>();
      })
      .def_static("adjacency_type", []() {
        return types::handle_for<typename ClusterSizeEstimate::AdjacencyType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<ClusterSizeEstimate>{}());
      }).def_static("__class_name__", []() {
        return type_str<ClusterSizeEstimate>{}();
      });
  }
};
}

void declare_typed_temporal_clusters(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_cluster_types>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
