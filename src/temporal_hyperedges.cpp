#include "bind_core.hpp"
#include <nanobind/operators.h>
#include <fmt/format.h>

#include <reticula/temporal_hyperedges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_hyperedges {
  void operator()(nb::module_& m) {
    define_basic_edge_concept<
        reticula::undirected_temporal_hyperedge<VertT, TimeT>>(m)
      .def(nb::init<std::vector<VertT>, TimeT>(),
          "verts"_a, "time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__init__", [](
                reticula::undirected_temporal_hyperedge<VertT, TimeT>* edge,
                std::tuple<std::vector<VertT>, TimeT> t) {
            new (edge) reticula::undirected_temporal_hyperedge<VertT, TimeT>{
                    std::get<0>(t), std::get<1>(t)};
        }, "tuple"_a,
        nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::pair<std::vector<VertT>, TimeT>,
      reticula::undirected_temporal_hyperedge<VertT, TimeT>>();

    define_basic_edge_concept<
        reticula::directed_temporal_hyperedge<VertT, TimeT>>(m)
      .def(nb::init<std::vector<VertT>, std::vector<VertT>, TimeT>(),
          "tails"_a, "heads"_a, "time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__init__", [](
                reticula::directed_temporal_hyperedge<VertT, TimeT> *edge,
                std::tuple<std::vector<VertT>, std::vector<VertT>, TimeT> t) {
           new (edge) reticula::directed_temporal_hyperedge<VertT, TimeT>{
                  std::get<0>(t), std::get<1>(t), std::get<2>(t)};
        }, "tuple"_a, nb::call_guard<nb::gil_scoped_release>())
      .def("heads",
          &reticula::directed_temporal_hyperedge<VertT, TimeT>::heads,
          nb::call_guard<nb::gil_scoped_release>())
      .def("tails",
          &reticula::directed_temporal_hyperedge<VertT, TimeT>::tails,
          nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::tuple<std::vector<VertT>, std::vector<VertT>, TimeT>,
      reticula::directed_temporal_hyperedge<VertT, TimeT>>();

    define_basic_edge_concept<
        reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>>(m)
      .def(nb::init<std::vector<VertT>, std::vector<VertT>, TimeT, TimeT>(),
          "tails"_a, "heads"_a, "cause_time"_a, "effect_time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__init__", [](
                reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>* edge,
                std::tuple<std::vector<VertT>, std::vector<VertT>, TimeT, TimeT> t) {
           new (edge) reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>{
                          std::get<0>(t), std::get<1>(t),
                          std::get<2>(t), std::get<3>(t)};
        }, "tuple"_a, nb::call_guard<nb::gil_scoped_release>())
      .def("heads",
          &reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>::heads,
          nb::call_guard<nb::gil_scoped_release>())
      .def("tails",
          &reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>::tails,
          nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::tuple<std::vector<VertT>, std::vector<VertT>, TimeT, TimeT>,
      reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>>();
  }
};

void declare_typed_temporal_hyperedges(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_hyperedges>>,
      types::first_order_temporal_type_parameter_combinations>>{}(m);
}
