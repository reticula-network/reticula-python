#include <metal.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <reticula/static_hyperedges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_static_hyperedges {
  void operator()(py::module &m) {
    define_basic_edge_concept<reticula::undirected_hyperedge<VertT>>(m)
      .def(py::init<std::vector<VertT>>(),
          "verts"_a);

    py::implicitly_convertible<
      std::vector<VertT>,
      reticula::undirected_hyperedge<VertT>>();

    define_basic_edge_concept<reticula::directed_hyperedge<VertT>>(m)
      .def(py::init<
          std::vector<VertT>,
          std::vector<VertT>>(),
          "tails"_a, "heads"_a)
      .def(py::init([](std::tuple<std::vector<VertT>, std::vector<VertT>> t) {
            return reticula::directed_hyperedge<VertT>(
                std::get<0>(t), std::get<1>(t));
          }), "tuple"_a)
      .def("heads",
          &reticula::directed_hyperedge<VertT>::heads)
      .def("tails",
          &reticula::directed_hyperedge<VertT>::tails);

    py::implicitly_convertible<
      std::pair<std::vector<VertT>, std::vector<VertT>>,
      reticula::directed_hyperedge<VertT>>();
  }
};


void declare_typed_static_hyperedges(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_hyperedges>,
      types::all_vert_types>>{}(m);
}
