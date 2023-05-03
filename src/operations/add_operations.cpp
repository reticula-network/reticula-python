#include <vector>
#include <unordered_map>

#include "../bind_core.hpp"

#include <reticula/operations.hpp>

#include "../type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::network_edge EdgeT>
struct declare_add_operation_algorithms {
  void operator()(nb::module_& m) {
    m.def("graph_union",
        &reticula::graph_union<EdgeT>,
        "g1"_a, "g2"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("with_edges",
        &reticula::with_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("with_edges",
        &reticula::with_edges<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("with_vertices",
        &reticula::with_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("with_vertices",
        &reticula::with_vertices<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_add_operation_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_add_operation_algorithms>,
      types::all_edge_types>>{}(m);
}
