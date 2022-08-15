#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <fmt/format.h>
#include <reticula/temporal_clusters.hpp>

#include "type_str/temporal_clusters.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::temporal_adjacency::temporal_adjacency AdjT>
struct declare_temporal_cluster_types {
  void operator()(py::module &m) {
    using EdgeT = AdjT::EdgeType;
    using Cluster = reticula::temporal_cluster<EdgeT, AdjT>;
    py::class_<Cluster>(m,
        python_type_str<Cluster>().c_str())
      .def(py::init<AdjT, std::size_t>(),
          "temporal_adjacency"_a, "size_hint"_a = 0,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init<std::vector<EdgeT>, AdjT, std::size_t>(),
          "events"_a,
          "temporal_adjacency"_a,
          "size_hint"_a = 0,
          py::call_guard<py::gil_scoped_release>())
      .def("insert",
          static_cast<void (Cluster::*)(
            const EdgeT&)>(
            &Cluster::insert),
          "event"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("insert",
          static_cast<void (Cluster::*)(
            const std::vector<EdgeT>&)>(
            &Cluster::insert),
          "events"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("merge", &Cluster::merge,
          "other"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("covers",
          &Cluster::covers,
          "vertex"_a, "time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("interval_sets",
          &Cluster::interval_sets,
          py::call_guard<py::gil_scoped_release>())
      .def("lifetime",
          &Cluster::lifetime,
          py::call_guard<py::gil_scoped_release>())
      .def("volume",
          &Cluster::volume,
          py::call_guard<py::gil_scoped_release>())
      .def("mass",
          &Cluster::mass,
          py::call_guard<py::gil_scoped_release>())
      .def(py::self == py::self,
          py::call_guard<py::gil_scoped_release>())
      .def(py::self != py::self,
          py::call_guard<py::gil_scoped_release>())
      .def("__len__", &Cluster::size,
          py::call_guard<py::gil_scoped_release>())
      .def("__contains__",
          &Cluster::contains,
          "event"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("__repr__", [](const Cluster& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename Cluster::VertexType>();
      })
      .def_static("adjacency_type", []() {
        return types::handle_for<typename Cluster::AdjacencyType>();
      });

    using ClusterSize = reticula::temporal_cluster_size<EdgeT, AdjT>;
    py::class_<ClusterSize>(m,
        python_type_str<ClusterSize>().c_str())
      .def("lifetime",
          &ClusterSize::lifetime,
          py::call_guard<py::gil_scoped_release>())
      .def("volume",
          &ClusterSize::volume,
          py::call_guard<py::gil_scoped_release>())
      .def("mass",
          &ClusterSize::mass,
          py::call_guard<py::gil_scoped_release>())
      .def("__repr__", [](const ClusterSize& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename ClusterSize::VertexType>();
      })
      .def_static("adjacency_type", []() {
        return types::handle_for<typename ClusterSize::AdjacencyType>();
      });


    using ClusterSizeEstimate =
      reticula::temporal_cluster_size_estimate<EdgeT, AdjT>;
    py::class_<ClusterSizeEstimate>(m,
        python_type_str<ClusterSizeEstimate>().c_str())
      .def("lifetime",
          &ClusterSizeEstimate::lifetime,
          py::call_guard<py::gil_scoped_release>())
      .def("volume_estimate",
          &ClusterSizeEstimate::volume_estimate,
          py::call_guard<py::gil_scoped_release>())
      .def("mass_estimate",
          &ClusterSizeEstimate::mass_estimate,
          py::call_guard<py::gil_scoped_release>())
      .def("__repr__", [](const ClusterSizeEstimate& c) {
          return fmt::format("{}", c);
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename ClusterSizeEstimate::VertexType>();
      })
      .def_static("adjacency_type", []() {
        return types::handle_for<typename ClusterSizeEstimate::AdjacencyType>();
      });
  }
};

void declare_typed_temporal_clusters(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_cluster_types>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
