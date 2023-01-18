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
struct declare_remove_operation_algorithms {
  void operator()(py::module& m) {
    m.def("without_edges",
        &reticula::without_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("without_edges",
        &reticula::without_edges<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("without_vertices",
        &reticula::without_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("without_vertices",
        &reticula::without_vertices<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_remove_operation_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_remove_operation_algorithms>,
      types::all_edge_types>>{}(m);
}
