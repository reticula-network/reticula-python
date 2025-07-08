#include <metal.hpp>
#include "bind_core.hpp"
#include <nanobind/operators.h>
#include <fmt/format.h>

#include <reticula/static_edges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT>
struct declare_static_edges {
  void operator()(nb::module_& m) {
    define_basic_edge_concept<reticula::undirected_edge<VertT>>(m)
      .def(nb::init<VertT, VertT>(), "v1"_a, "v2"_a)
      .def("__init__", [](
          reticula::undirected_edge<VertT>* edge,
          std::tuple<VertT, VertT> t) {
        new (edge) reticula::undirected_edge<VertT>{
          std::get<0>(t), std::get<1>(t)};
      }, "tuple"_a, nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::tuple<VertT, VertT>,
      reticula::undirected_edge<VertT>>();

    define_basic_edge_concept<reticula::directed_edge<VertT>>(m)
      .def(nb::init<VertT, VertT>(),
          "tail"_a, "head"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__init__", [](
          reticula::directed_edge<VertT>* edge,
          std::tuple<VertT, VertT> t) {
        new (edge) reticula::directed_edge<VertT>{
          std::get<0>(t), std::get<1>(t)};
      }, "tuple"_a, nb::call_guard<nb::gil_scoped_release>())
      .def("head",
          &reticula::directed_edge<VertT>::head,
          nb::call_guard<nb::gil_scoped_release>())
      .def("tail",
          &reticula::directed_edge<VertT>::tail,
          nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::tuple<VertT, VertT>,
      reticula::directed_edge<VertT>>();
  }
};
}


void declare_typed_static_edges(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_edges>,
      types::all_vert_types>>{}(m);
}
