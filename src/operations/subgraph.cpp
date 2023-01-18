#include <vector>
#include <unordered_map>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include <reticula/operations.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::network_edge EdgeT>
struct declare_subgraph_algorithms {
  void operator()(py::module& m) {
    m.def("vertex_induced_subgraph",
        &reticula::vertex_induced_subgraph<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("vertex_induced_subgraph",
        &reticula::vertex_induced_subgraph<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("edge_induced_subgraph",
        &reticula::edge_induced_subgraph<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("edge_induced_subgraph",
        &reticula::edge_induced_subgraph<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_subgraph_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_subgraph_algorithms>,
      types::all_edge_types>>{}(m);
}
