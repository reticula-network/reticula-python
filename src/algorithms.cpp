#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>

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

template <typename T>
struct declare_degree_sequence_algorithms {
  void operator()(py::module& m) {
    m.def("is_graphic",
        &reticula::is_graphic<std::vector<T>>,
        "degree_seq"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("is_digraphic",
        &reticula::is_digraphic<std::vector<std::pair<T, T>>>,
        "in_out_degree_seq"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_assortativity_algorithms(py::module& m);
void declare_typed_degree_algorithms(py::module& m);
void declare_typed_basic_operation_algorithms(py::module& m);
void declare_typed_basic_temporal_network_algorithms(py::module& m);
void declare_typed_density_algorithms(py::module& m);
void declare_typed_directed_connectivity_algorithms(py::module& m);
void declare_typed_occupation_algorithms(py::module& m);
void declare_typed_subgraph_algorithms(py::module& m);
void declare_typed_temporal_adjacency_algorithms(py::module& m);
void declare_typed_undirected_connectivity_algorithms(py::module& m);

void declare_typed_algorithms(py::module& m) {
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

  types::run_each<
    metal::transform<
      metal::lambda<declare_degree_sequence_algorithms>,
        metal::list<uint64_t>>>{}(m);

  declare_typed_assortativity_algorithms(m);
  declare_typed_degree_algorithms(m);
  declare_typed_basic_operation_algorithms(m);
  declare_typed_basic_temporal_network_algorithms(m);
  declare_typed_density_algorithms(m);
  declare_typed_directed_connectivity_algorithms(m);
  declare_typed_occupation_algorithms(m);
  declare_typed_subgraph_algorithms(m);
  declare_typed_temporal_adjacency_algorithms(m);
  declare_typed_undirected_connectivity_algorithms(m);
}
