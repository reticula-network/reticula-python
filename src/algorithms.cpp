#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>
#include <dag/dag.hpp>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_directed_network_algorithms {
  void operator()(py::module& m) {
    m.def("topological_order", &dag::topological_order<VertT>,
        "directed_network"_a);
    m.def("out_component", &dag::out_component<VertT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0);
    m.def("in_component", &dag::in_component<VertT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0);
    m.def("weakly_connected_components",
        &dag::weakly_connected_components<VertT>,
        "directed_network"_a, "singleton"_a = true);
  }
};


template <typename OutVert, typename InVert>
struct declare_relabel_nodes {
  void operator()(py::module& m) {
    m.def(fmt::format("relabel_nodes_{}", type_str<OutVert>{}()).c_str(),
        &dag::relabel_nodes<OutVert, InVert>,
        "network"_a);
  }
};

template <typename VertT1, typename VertT2>
struct declare_cartesian_product {
  void operator()(py::module& m) {
    m.def("cartesian_product", &dag::cartesian_product<VertT1, VertT2>,
        "undirected_net_1"_a, "undirected_net_2"_a);
  }
};

struct declare_is_graphic {
  void operator()(py::module& m) {
    m.def("is_graphic", &dag::is_graphic<std::vector<uint64_t>>,
        "degree_seq"_a);
  }
};

void declare_typed_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_directed_network_algorithms>,
      types::first_order_vert_types>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_directed_network_algorithms>,
      types::first_order_temporal_edges>>{}(m);

  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_relabel_nodes>>,
      metal::cartesian<types::integer_vert_types, types::first_order_vert_types>
    >>{}(m);

  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_cartesian_product>>,
      metal::cartesian<types::first_order_vert_types, types::first_order_vert_types>
    >>{}(m);

  declare_is_graphic{}(m);
}
