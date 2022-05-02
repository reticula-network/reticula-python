#include <nanobind/nanobind.h>
#include <nanobind/stl.h>
#include <nanobind/operators.h>

#include <fmt/format.h>
#include <dag/temporal_clusters.hpp>

#include "type_str/temporal_clusters.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <dag::temporal_adjacency::temporal_adjacency AdjT>
struct declare_temporal_cluster_types {
  void operator()(nb::module_ &m) {
    using EdgeT = AdjT::EdgeType;
    using Cluster = dag::temporal_cluster<EdgeT, AdjT>;
    nb::class_<Cluster>(m,
        python_type_str<Cluster>().c_str())
      .def(nb::init<AdjT, std::size_t>(),
          "temporal_adjacency"_a, "size_hint"_a = 0)
      .def(nb::init<std::vector<EdgeT>, AdjT, std::size_t>(),
          "events"_a,
          "temporal_adjacency"_a,
          "size_hint"_a = 0)
      .def("insert",
          static_cast<void (Cluster::*)(
            const EdgeT&)>(
            &Cluster::insert),
          "event"_a)
      .def("insert",
          static_cast<void (Cluster::*)(
            const std::vector<EdgeT>&)>(
            &Cluster::insert),
          "events"_a)
      .def("merge", &Cluster::merge,
          "other"_a)
      .def("covers",
          &Cluster::covers,
          "vertex"_a, "time"_a)
      .def("interval_sets",
          &Cluster::interval_sets)
      .def("lifetime",
          &Cluster::lifetime)
      .def("volume",
          &Cluster::volume)
      .def("mass",
          &Cluster::mass)
      .def(nb::self == nb::self)
      .def(nb::self != nb::self)
      .def("__len__", &Cluster::size)
      .def("__contains__",
          &Cluster::contains,
          "event"_a)
      .def("__repr__", [](const Cluster& c) {
          return fmt::format("{}", c);
      });

    using ClusterSize = dag::temporal_cluster_size<EdgeT, AdjT>;
    nb::class_<ClusterSize>(m,
        python_type_str<ClusterSize>().c_str())
      .def("lifetime",
          &ClusterSize::lifetime)
      .def("volume",
          &ClusterSize::volume)
      .def("mass",
          &ClusterSize::mass)
      .def("__repr__", [](const ClusterSize& c) {
          return fmt::format("{}", c);
      });


    using ClusterSizeEstimate =
      dag::temporal_cluster_size_estimate<EdgeT, AdjT>;
    nb::class_<ClusterSizeEstimate>(m,
        python_type_str<ClusterSizeEstimate>().c_str())
      .def("lifetime",
          &ClusterSizeEstimate::lifetime)
      .def("volume_estimate",
          &ClusterSizeEstimate::volume_estimate)
      .def("mass_estimate",
          &ClusterSizeEstimate::mass_estimate)
      .def("__repr__", [](const ClusterSizeEstimate& c) {
          return fmt::format("{}", c);
      });
  }
};

void declare_typed_temporal_clusters(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_cluster_types>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
