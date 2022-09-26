#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::static_edge EdgeT>
struct declare_density_algorithm {
  void operator()(py::module& m) {
    m.def("density",
        py::overload_cast<const reticula::network<EdgeT>&>(
          &reticula::density<typename EdgeT::VertexType>),
        "network"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_density_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_density_algorithm>,
      metal::join<
        types::first_order_undirected_edges,
        types::second_order_undirected_edges,
        types::first_order_directed_edges,
        types::second_order_directed_edges>>>{}(m);
}
