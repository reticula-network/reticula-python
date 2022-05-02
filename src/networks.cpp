#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl.h>
#include <fmt/format.h>

#include <dag/networks.hpp>

#include "type_str/networks.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <dag::network_edge EdgeT>
struct declare_network_class {
  void operator()(nb::module &m) {
    using Net = dag::network<EdgeT>;
    nb::class_<Net>(m,
        python_type_str<Net>().c_str())
      .def(nb::init<>())
      .def(nb::init<std::vector<EdgeT>>(),
          "edges"_a)
      .def(nb::init<
            std::vector<EdgeT>,
            std::vector<typename EdgeT::VertexType>>(),
          "edges"_a, "verts"_a)
      .def("vertices",
          &Net::vertices)
      .def("edges",
          &Net::edges)
      .def("edges_cause",
          &Net::edges_cause)
      .def("edges_effect",
          &Net::edges_effect)
      .def("incident_edges",
          &Net::incident_edges,
          "vert"_a)
      .def("in_degree",
          &Net::in_degree,
          "vert"_a)
      .def("out_degree",
          &Net::out_degree,
          "vert"_a)
      .def("degree",
          &Net::degree,
          "vert"_a)
      .def("predecessors",
          &Net::predecessors,
          "vert"_a)
      .def("successors",
          &Net::successors,
          "vert"_a)
      .def("neighbours",
          &Net::neighbours,
          "vert"_a)
      .def("in_edges",
          nb::overload_cast<const typename EdgeT::VertexType&>(
            &Net::in_edges, nb::const_),
          "vert"_a)
      .def("out_edges",
          nb::overload_cast<const typename EdgeT::VertexType&>(
            &Net::out_edges, nb::const_),
          "vert"_a)
      .def("in_edges",
          nb::overload_cast<>(
            &Net::in_edges, nb::const_))
      .def("out_edges",
          nb::overload_cast<>(
            &Net::out_edges, nb::const_))
      .def("__repr__", [](const Net& a) {
        return fmt::format("{}", a);
      })
      .def_static("edge_type", []() {
        return nb::type::of<typename Net::EdgeType>();
      });
  }
};

void declare_typed_networks(nb::module& m) {
  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_network_class>,
      types::all_edge_types>>{}(m);
}
