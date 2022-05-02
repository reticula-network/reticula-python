#include <metal.hpp>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl.h>
#include <fmt/format.h>

#include <dag/static_edges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT>
struct declare_static_edges {
  void operator()(nb::module &m) {
    define_basic_edge_concept<dag::undirected_edge<VertT>>(m)
      .def(nb::init<VertT, VertT>(), "v1"_a, "v2"_a)
      .def(nb::init([](std::tuple<VertT, VertT> t) {
            return dag::undirected_edge<VertT>(
                std::get<0>(t), std::get<1>(t));
            }), "tuple"_a);

    nb::implicitly_convertible<
      std::tuple<VertT, VertT>,
      dag::undirected_edge<VertT>>();

    define_basic_edge_concept<dag::directed_edge<VertT>>(m)
      .def(nb::init<VertT, VertT>(),
          "tail"_a, "head"_a)
      .def(nb::init([](std::tuple<VertT, VertT> t) {
            return dag::directed_edge<VertT>(
                std::get<0>(t), std::get<1>(t));
            }), "tuple"_a)
      .def("head",
          &dag::directed_edge<VertT>::head)
      .def("tail",
          &dag::directed_edge<VertT>::tail);

    nb::implicitly_convertible<
      std::tuple<VertT, VertT>,
      dag::directed_edge<VertT>>();
  }
};


void declare_typed_static_edges(nb::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_edges>,
      types::all_vert_types>>{}(m);
}
