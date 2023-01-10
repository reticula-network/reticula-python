#include <vector>
#include <unordered_map>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::network_edge EdgeT>
struct declare_add_operation_algorithms {
  void operator()(py::module& m) {
    m.def("graph_union",
        &reticula::graph_union<EdgeT>,
        "g1"_a, "g2"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_edges",
        &reticula::with_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_edges",
        &reticula::with_edges<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_vertices",
        &reticula::with_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_vertices",
        &reticula::with_vertices<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_add_operation_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_add_operation_algorithms>,
      types::all_edge_types>>{}(m);
}
