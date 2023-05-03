#include <vector>
#include <unordered_map>

#include "../bind_core.hpp"

#include <reticula/operations.hpp>

#include "../type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::network_edge EdgeT>
struct declare_remove_operation_algorithms {
  void operator()(nb::module_& m) {
    m.def("without_edges",
        &reticula::without_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("without_edges",
        &reticula::without_edges<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("without_vertices",
        &reticula::without_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("without_vertices",
        &reticula::without_vertices<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_remove_operation_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_remove_operation_algorithms>,
      types::all_edge_types>>{}(m);
}
