#include "../bind_core.hpp"

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::static_network_edge EdgeT>
struct declare_density_algorithm {
  void operator()(nb::module_& m) {
    m.def("density",
        nb::overload_cast<const reticula::network<EdgeT>&>(
          &reticula::density<typename EdgeT::VertexType>),
        "network"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};
}

void declare_typed_density_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_density_algorithm>,
      metal::join<
        types::first_order_undirected_edges,
        types::second_order_undirected_edges,
        types::first_order_directed_edges,
        types::second_order_directed_edges>>>{}(m);
}
