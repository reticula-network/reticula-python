#include <metal.hpp>
#include "bind_core.hpp"
#include <nanobind/operators.h>
#include <fmt/format.h>

#include <reticula/static_hyperedges.hpp>

#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT>
struct declare_static_hyperedges {
  void operator()(nb::module_ &m) {
    define_basic_edge_concept<reticula::undirected_hyperedge<VertT>>(m)
      .def(nb::init<const std::vector<VertT>&>(),
           "verts"_a, nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::vector<VertT>,
      reticula::undirected_hyperedge<VertT>>();

    define_basic_edge_concept<reticula::directed_hyperedge<VertT>>(m)
      .def(nb::init<const std::vector<VertT>&, const std::vector<VertT>&>(),
           "tails"_a, "heads"_a,
           nb::call_guard<nb::gil_scoped_release>())
      .def("__init__", [](
          reticula::directed_hyperedge<VertT>* edge,
          const std::tuple<std::vector<VertT>, std::vector<VertT>>& t) {
        new (edge) reticula::directed_hyperedge<VertT>{
          std::get<0>(t), std::get<1>(t)};
      }, "tuple"_a, nb::call_guard<nb::gil_scoped_release>())
      .def("heads", [](const reticula::directed_hyperedge<VertT>& self) {
        auto heads = self.heads();
        return std::vector<VertT>(heads.begin(), heads.end());
      }, nb::call_guard<nb::gil_scoped_release>())
      .def("tails", [](const reticula::directed_hyperedge<VertT>& self) {
        auto tails = self.tails();
        return std::vector<VertT>(tails.begin(), tails.end());
      }, nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::pair<std::vector<VertT>, std::vector<VertT>>,
      reticula::directed_hyperedge<VertT>>();
  }
};
}


void declare_typed_static_hyperedges(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_hyperedges>,
      types::first_order_vert_types>>{}(m);
}
