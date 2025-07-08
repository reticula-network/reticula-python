#include "bind_core.hpp"

#include <reticula/operations.hpp>

#include "type_str/edges.hpp"
#include "type_str/scalars.hpp"

#include "type_utils.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <typename OutVert, typename InVert>
struct declare_relabel_nodes {
  void operator()(nb::module_& m) {
    m.def(fmt::format("relabel_nodes_{}", python_type_str<OutVert>()).c_str(),
        &reticula::relabel_nodes<OutVert, InVert>,
        "network"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

template <typename VertT1, typename VertT2>
struct declare_cartesian_product {
  void operator()(nb::module_& m) {
    m.def("cartesian_product",
        &reticula::cartesian_product<VertT1, VertT2>,
        "undirected_net_1"_a, "undirected_net_2"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};
}


void declare_typed_add_operation_algorithms(nb::module_& m);
void declare_typed_remove_operation_algorithms(nb::module_& m);

void declare_typed_edge_occupation_algorithms(nb::module_& m);
void declare_typed_vertex_occupation_algorithms(nb::module_& m);

void declare_typed_subgraph_algorithms(nb::module_& m);

void declare_operations(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_relabel_nodes>>,
      metal::cartesian<
        types::integer_vert_types,
        types::first_order_vert_types>>>{}(m);

  types::run_each<
    metal::transform<
      metal::bind<
        metal::lambda<declare_cartesian_product>,
        metal::_1, metal::_1>,
      types::simple_vert_types>>{}(m);

  declare_typed_add_operation_algorithms(m);
  declare_typed_remove_operation_algorithms(m);

  declare_typed_edge_occupation_algorithms(m);
  declare_typed_vertex_occupation_algorithms(m);

  declare_typed_subgraph_algorithms(m);
}
