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
    m.def("is_acyclic",
        &dag::is_acyclic<VertT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("topological_order",
        &dag::topological_order<VertT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("out_component",
        &dag::out_component<VertT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_components",
        &dag::out_components<VertT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_component_sizes",
        &dag::out_component_sizes<VertT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("out_component_size_estimates",
        &dag::out_component_size_estimates<VertT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("in_component",
        &dag::in_component<VertT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_components",
        &dag::in_components<VertT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_component_sizes",
        &dag::in_component_sizes<VertT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("in_component_size_estimates",
        &dag::in_component_size_estimates<VertT>,
        "directed_network"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("weakly_connected_component",
        &dag::weakly_connected_component<VertT>,
        "directed_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("weakly_connected_components",
        &dag::weakly_connected_components<VertT>,
        "directed_network"_a, "singletons"_a = true,
        py::call_guard<py::gil_scoped_release>());

    m.def("connected_component",
        &dag::connected_component<VertT>,
        "undirected_network"_a, "vert"_a, "size_hint"_a = 0,
        py::call_guard<py::gil_scoped_release>());
    m.def("connected_components",
        &dag::connected_components<VertT>,
        "undirected_network"_a, "singletons"_a = true,
        py::call_guard<py::gil_scoped_release>());
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
      types::all_vert_types>>{}(m);

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
      metal::cartesian<types::simple_vert_types, types::simple_vert_types>
    >>{}(m);

  declare_is_graphic{}(m);
}
