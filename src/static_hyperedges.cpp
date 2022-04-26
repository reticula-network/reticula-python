#include <metal.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <dag/static_hyperedges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_static_hyperedges {
  void operator()(py::module &m) {
    define_basic_edge_concept<dag::undirected_hyperedge<VertT>>(m)
      .def(py::init<std::vector<VertT>>(),
          "verts"_a);

    define_basic_edge_concept<dag::directed_hyperedge<VertT>>(m)
      .def(py::init<
          std::vector<VertT>,
          std::vector<VertT>>(),
          "tails"_a, "heads"_a)
      .def("heads",
          &dag::directed_hyperedge<VertT>::heads)
      .def("tails",
          &dag::directed_hyperedge<VertT>::tails);
  }
};


void declare_typed_static_hyperedges(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_hyperedges>,
      types::all_vert_types>>{}(m);
}
