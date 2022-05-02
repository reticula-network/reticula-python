#include <metal.hpp>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl.h>
#include <fmt/format.h>

#include <dag/static_hyperedges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT>
struct declare_static_hyperedges {
  void operator()(nb::module &m) {
    define_basic_edge_concept<dag::undirected_hyperedge<VertT>>(m)
      .def(nb::init<std::vector<VertT>>(),
          "verts"_a);

    nb::implicitly_convertible<
      std::vector<VertT>,
      dag::undirected_hyperedge<VertT>>();

    define_basic_edge_concept<dag::directed_hyperedge<VertT>>(m)
      .def(nb::init<
          std::vector<VertT>,
          std::vector<VertT>>(),
          "tails"_a, "heads"_a)
      .def(nb::init([](std::tuple<std::vector<VertT>, std::vector<VertT>> t) {
            return dag::directed_hyperedge<VertT>(
                std::get<0>(t), std::get<1>(t));
          }), "tuple"_a)
      .def("heads",
          &dag::directed_hyperedge<VertT>::heads)
      .def("tails",
          &dag::directed_hyperedge<VertT>::tails);

    nb::implicitly_convertible<
      std::pair<std::vector<VertT>, std::vector<VertT>>,
      dag::directed_hyperedge<VertT>>();
  }
};


void declare_typed_static_hyperedges(nb::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_hyperedges>,
      types::all_vert_types>>{}(m);
}
