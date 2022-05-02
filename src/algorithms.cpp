#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/stl.h>

#include <dag/algorithms.hpp>

#include "type_str/edges.hpp"
#include "type_str/scalars.hpp"

#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename OutVert, typename InVert>
struct declare_relabel_nodes {
  void operator()(nb::module& m) {
    m.def(fmt::format("relabel_nodes_{}", python_type_str<OutVert>()).c_str(),
        &dag::relabel_nodes<OutVert, InVert>,
        "network"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

template <typename VertT1, typename VertT2>
struct declare_cartesian_product {
  void operator()(nb::module& m) {
    m.def("cartesian_product",
        &dag::cartesian_product<VertT1, VertT2>,
        "undirected_net_1"_a, "undirected_net_2"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

template <typename T>
struct declare_degree_sequence_algorithms {
  void operator()(nb::module& m) {
    m.def("is_graphic",
        &dag::is_graphic<std::vector<T>>,
        "degree_seq"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("is_digraphic",
        &dag::is_digraphic<std::vector<std::pair<T, T>>>,
        "in_out_degree_seq"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};


void declare_typed_directed_algorithms(nb::module& m);
void declare_typed_undirected_algorithms(nb::module& m);
void declare_typed_temporal_algorithms(nb::module& m);

void declare_typed_algorithms(nb::module& m) {
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

  declare_typed_directed_algorithms(m);
  declare_typed_undirected_algorithms(m);
  declare_typed_temporal_algorithms(m);
}
