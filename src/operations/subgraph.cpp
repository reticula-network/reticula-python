#include <vector>
#include <unordered_map>

#include "../bind_core.hpp"

#include <reticula/operations.hpp>

#include "../type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::network_edge EdgeT>
struct declare_subgraph_algorithms {
  void operator()(nb::module_& m) {
    m.def("vertex_induced_subgraph",
        &reticula::vertex_induced_subgraph<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("vertex_induced_subgraph",
        &reticula::vertex_induced_subgraph<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("edge_induced_subgraph",
        &reticula::edge_induced_subgraph<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("edge_induced_subgraph",
        &reticula::edge_induced_subgraph<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_subgraph_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_subgraph_algorithms>,
      types::all_edge_types>>{}(m);
}
