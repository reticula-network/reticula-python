#include <metal.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <dag/static_edges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_static_edges {
  void operator()(py::module &m) {
    define_basic_edge_concept<dag::undirected_edge<VertT>>(m)
        .def(py::init<VertT, VertT>());

    define_basic_edge_concept<dag::directed_edge<VertT>>(m)
      .def(py::init<VertT, VertT>(),
          "tail"_a, "head"_a)
      .def("head",
          &dag::directed_edge<VertT>::head)
      .def("tail",
          &dag::directed_edge<VertT>::tail);
  }
};


void declare_typed_static_edges(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_edges>,
      types::all_vert_types>>{}(m);
}
