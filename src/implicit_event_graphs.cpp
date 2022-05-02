#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/stl.h>

#include <fmt/format.h>

#include <dag/implicit_event_graph.hpp>

#include "type_str/implicit_event_graphs.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <dag::temporal_adjacency::temporal_adjacency AdjT>
struct declare_implicit_event_graph_class {
  void operator()(nb::module &m) {
    using EdgeT = AdjT::EdgeType;
    using Net = dag::implicit_event_graph<EdgeT, AdjT>;
    nb::class_<Net>(m,
        python_type_str<Net>().c_str())
      .def(nb::init<std::vector<EdgeT>, AdjT>(),
          "events"_a, "temporal_adjacency"_a)
      .def(nb::init<
            std::vector<EdgeT>,
            std::vector<typename EdgeT::VertexType>,
            AdjT>(),
          "events"_a, "verts"_a, "temporal_adjacency"_a)
      .def(nb::init<dag::network<EdgeT>, AdjT>(),
          "temporal_network"_a, "temporal_adjacency"_a)
      .def("events_cause",
          &Net::events_cause)
      .def("events_effect",
          &Net::events_effect)
      .def("temporal_net_vertices",
          &Net::temporal_net_vertices)
      .def("temporal_adjacency",
          &Net::temporal_adjacency)
      .def("time_window",
          &Net::time_window)
      .def("predecessors",
          &Net::predecessors,
          "event"_a, "just_first"_a = true)
      .def("successors",
          &Net::successors,
          "event"_a, "just_first"_a = true)
      .def("neighbours",
          &Net::neighbours,
          "event"_a, "just_first"_a = true)
      .def("__repr__", [](const Net& a) {
        return fmt::format("{}", a);
      });
  }
};

void declare_typed_implicit_event_graphs(nb::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_implicit_event_graph_class>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
