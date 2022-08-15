#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <fmt/format.h>

#include <reticula/implicit_event_graphs.hpp>

#include "type_str/implicit_event_graphs.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::temporal_adjacency::temporal_adjacency AdjT>
struct declare_implicit_event_graph_class {
  void operator()(py::module &m) {
    using EdgeT = AdjT::EdgeType;
    using Net = reticula::implicit_event_graph<EdgeT, AdjT>;
    py::class_<Net>(m,
        python_type_str<Net>().c_str())
      .def(py::init<std::vector<EdgeT>, AdjT>(),
          "events"_a, "temporal_adjacency"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init<
            std::vector<EdgeT>,
            std::vector<typename EdgeT::VertexType>,
            AdjT>(),
          "events"_a, "verts"_a, "temporal_adjacency"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init<reticula::network<EdgeT>, AdjT>(),
          "temporal_network"_a, "temporal_adjacency"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("events_cause",
          &Net::events_cause,
          py::call_guard<py::gil_scoped_release>())
      .def("events_effect",
          &Net::events_effect,
          py::call_guard<py::gil_scoped_release>())
      .def("temporal_net_vertices",
          &Net::temporal_net_vertices,
          py::call_guard<py::gil_scoped_release>())
      .def("temporal_adjacency",
          &Net::temporal_adjacency,
          py::call_guard<py::gil_scoped_release>())
      .def("time_window",
          &Net::time_window,
          py::call_guard<py::gil_scoped_release>())
      .def("predecessors",
          &Net::predecessors,
          "event"_a, "just_first"_a = true,
          py::call_guard<py::gil_scoped_release>())
      .def("successors",
          &Net::successors,
          "event"_a, "just_first"_a = true,
          py::call_guard<py::gil_scoped_release>())
      .def("neighbours",
          &Net::neighbours,
          "event"_a, "just_first"_a = true,
          py::call_guard<py::gil_scoped_release>())
      .def("__repr__", [](const Net& a) {
        return fmt::format("{}", a);
      })
      .def_static("edge_type", []() {
        return types::handle_for<typename Net::EdgeType>();
      })
      .def_static("vertex_type", []() {
        return types::handle_for<typename Net::VertexType>();
      });
  }
};

void declare_typed_implicit_event_graphs(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_implicit_event_graph_class>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
