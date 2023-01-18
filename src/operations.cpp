#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <reticula/operations.hpp>

#include "type_str/edges.hpp"
#include "type_str/scalars.hpp"

#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename OutVert, typename InVert>
struct declare_relabel_nodes {
  void operator()(py::module& m) {
    m.def(fmt::format("relabel_nodes_{}", python_type_str<OutVert>()).c_str(),
        &reticula::relabel_nodes<OutVert, InVert>,
        "network"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

template <typename VertT1, typename VertT2>
struct declare_cartesian_product {
  void operator()(py::module& m) {
    m.def("cartesian_product",
        &reticula::cartesian_product<VertT1, VertT2>,
        "undirected_net_1"_a, "undirected_net_2"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};


void declare_typed_add_operation_algorithms(py::module& m);
void declare_typed_remove_operation_algorithms(py::module& m);

void declare_typed_edge_occupation_algorithms(py::module& m);
void declare_typed_vertex_occupation_algorithms(py::module& m);

void declare_typed_subgraph_algorithms(py::module& m);

void declare_operations(py::module& m) {
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
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_cartesian_product>>,
      metal::cartesian<
        types::simple_vert_types,
        types::simple_vert_types>>>{}(m);

  declare_typed_add_operation_algorithms(m);
  declare_typed_remove_operation_algorithms(m);

  declare_typed_edge_occupation_algorithms(m);
  declare_typed_vertex_occupation_algorithms(m);

  declare_typed_subgraph_algorithms(m);
}
