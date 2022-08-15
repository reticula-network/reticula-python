#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <reticula/networks.hpp>

#include "type_str/networks.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::network_edge EdgeT>
struct declare_network_class {
  void operator()(py::module &m) {
    using Net = reticula::network<EdgeT>;
    py::class_<Net>(m,
        python_type_str<Net>().c_str())
      .def(py::init<>(),
          py::call_guard<py::gil_scoped_release>())
      .def(py::init<std::vector<EdgeT>>(),
          "edges"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init<
            std::vector<EdgeT>,
            std::vector<typename EdgeT::VertexType>>(),
          "edges"_a, "verts"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("vertices",
          &Net::vertices,
          py::call_guard<py::gil_scoped_release>())
      .def("edges",
          &Net::edges,
          py::call_guard<py::gil_scoped_release>())
      .def("edges_cause",
          &Net::edges_cause,
          py::call_guard<py::gil_scoped_release>())
      .def("edges_effect",
          &Net::edges_effect,
          py::call_guard<py::gil_scoped_release>())
      .def("incident_edges",
          &Net::incident_edges,
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("in_degree",
          &Net::in_degree,
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("out_degree",
          &Net::out_degree,
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("degree",
          &Net::degree,
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("predecessors",
          &Net::predecessors,
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("successors",
          &Net::successors,
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("neighbours",
          &Net::neighbours,
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("in_edges",
          py::overload_cast<const typename EdgeT::VertexType&>(
            &Net::in_edges, py::const_),
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("out_edges",
          py::overload_cast<const typename EdgeT::VertexType&>(
            &Net::out_edges, py::const_),
          "vert"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("in_edges",
          py::overload_cast<>(
            &Net::in_edges, py::const_),
          py::call_guard<py::gil_scoped_release>())
      .def("out_edges",
          py::overload_cast<>(
            &Net::out_edges, py::const_),
          py::call_guard<py::gil_scoped_release>())
      .def(py::self == py::self,
          py::call_guard<py::gil_scoped_release>())
      .def(py::self != py::self,
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

void declare_typed_networks(py::module& m) {
  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_network_class>,
      types::all_edge_types>>{}(m);
}
