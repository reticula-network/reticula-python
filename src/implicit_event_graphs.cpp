#include <vector>

#include "bind_core.hpp"

#include <fmt/format.h>

#include <reticula/implicit_event_graphs.hpp>

#include "type_str/implicit_event_graphs.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::temporal_adjacency::temporal_adjacency AdjT>
struct declare_implicit_event_graph_class {
  void operator()(nb::module_ &m) {
    using EdgeT = typename AdjT::EdgeType;
    using Net = reticula::implicit_event_graph<EdgeT, AdjT>;
    nb::class_<Net>(
        m, python_type_str<Net>().c_str())
      .def(nb::init<const Net&>(),
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::init<const std::vector<EdgeT>&, AdjT>(),
          "events"_a, "temporal_adjacency"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::init<
            const std::vector<EdgeT>&,
            const std::vector<typename EdgeT::VertexType>&,
            const AdjT&>(),
          "events"_a, "verts"_a, "temporal_adjacency"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def(nb::init<const reticula::network<EdgeT>&, const AdjT&>(),
          "temporal_network"_a, "temporal_adjacency"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("events_cause",
           [](const Net& self) {
             auto edges = self.events_cause();
             return std::vector<EdgeT>(edges.begin(), edges.end());
           }, nb::call_guard<nb::gil_scoped_release>())
      .def("events_effect",
           [](const Net& self) {
             auto edges = self.events_effect();
             return std::vector<EdgeT>(edges.begin(), edges.end());
           }, nb::call_guard<nb::gil_scoped_release>())
      .def("temporal_net_vertices",
           [](const Net& self) {
             auto verts = self.temporal_net_vertices();
             return std::vector<typename Net::VertexType>(verts.begin(), verts.end());
           }, nb::call_guard<nb::gil_scoped_release>())
      .def("temporal_adjacency",
          &Net::temporal_adjacency,
          nb::call_guard<nb::gil_scoped_release>())
      .def("time_window",
          &Net::time_window,
          nb::call_guard<nb::gil_scoped_release>())
      .def("predecessors",
          &Net::predecessors,
          "event"_a, "just_first"_a = true,
          nb::call_guard<nb::gil_scoped_release>())
      .def("successors",
          &Net::successors,
          "event"_a, "just_first"_a = true,
          nb::call_guard<nb::gil_scoped_release>())
      .def("neighbours",
          &Net::neighbours,
          "event"_a, "just_first"_a = true,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__copy__", [](const Net& self) {
          return Net(self);
      }).def("__deepcopy__", [](const Net& self, nb::dict) {
          return Net(self);
      }, "memo"_a)
      .def("__repr__", [](const Net& a) {
        return fmt::format("{}", a);
      }).def_static("edge_type", []() {
        return types::handle_for<typename Net::EdgeType>();
      }).def_static("vertex_type", []() {
        return types::handle_for<typename Net::VertexType>();
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<Net>{}());
      }).def_static("__class_name__", []() {
        return type_str<Net>{}();
      });
  }
};
}

void declare_typed_implicit_event_graphs(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_implicit_event_graph_class>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
