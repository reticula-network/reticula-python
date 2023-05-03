#include "bind_core.hpp"
#include <nanobind/operators.h>
#include <fmt/format.h>

#include <reticula/temporal_edges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_edges {
  void operator()(nb::module_ &m) {
    define_basic_edge_concept<reticula::undirected_temporal_edge<VertT, TimeT>>(m)
      .def(nb::init<VertT, VertT, TimeT>(),
          "v1"_a, "v2"_a, "time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__init__", [](reticula::undirected_temporal_edge<VertT, TimeT>* edge,
                          std::tuple<VertT, VertT, TimeT> t) {
            new (edge) reticula::undirected_temporal_edge<VertT, TimeT>{
                std::get<0>(t), std::get<1>(t), std::get<2>(t)};
           },
          "tuple"_a,
          nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT>,
      reticula::undirected_temporal_edge<VertT, TimeT>>();

    define_basic_edge_concept<reticula::directed_temporal_edge<VertT, TimeT>>(m)
      .def(nb::init<VertT, VertT, TimeT>(),
          "tail"_a, "head"_a, "time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__init__", [](
           reticula::directed_temporal_edge<VertT, TimeT>* edge,
           std::tuple<VertT, VertT, TimeT> t) {
              new (edge) reticula::directed_temporal_edge<VertT, TimeT>{
                  std::get<0>(t), std::get<1>(t), std::get<2>(t)};
          }, "tuple"_a, nb::call_guard<nb::gil_scoped_release>())
      .def("head",
          &reticula::directed_temporal_edge<VertT, TimeT>::head,
          nb::call_guard<nb::gil_scoped_release>())
      .def("tail",
          &reticula::directed_temporal_edge<VertT, TimeT>::tail,
          nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT>,
      reticula::directed_temporal_edge<VertT, TimeT>>();

    define_basic_edge_concept<
        reticula::directed_delayed_temporal_edge<VertT, TimeT>>(m)
      .def(nb::init<VertT, VertT, TimeT, TimeT>(),
          "tail"_a, "head"_a, "cause_time"_a, "effect_time"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__init__", [](
        reticula::directed_delayed_temporal_edge<VertT, TimeT> *edge,
        std::tuple<VertT, VertT, TimeT, TimeT> t) {
            new (edge) reticula::directed_delayed_temporal_edge<VertT, TimeT>{
                std::get<0>(t), std::get<1>(t), std::get<2>(t), std::get<3>(t)};
        }, "tuple"_a, nb::call_guard<nb::gil_scoped_release>())
      .def("head",
          &reticula::directed_delayed_temporal_edge<VertT, TimeT>::head,
          nb::call_guard<nb::gil_scoped_release>())
      .def("tail",
          &reticula::directed_delayed_temporal_edge<VertT, TimeT>::tail,
          nb::call_guard<nb::gil_scoped_release>());

    nb::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT, TimeT>,
      reticula::directed_delayed_temporal_edge<VertT, TimeT>>();
  }
};

void declare_typed_temporal_edges(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_edges>>,
      types::first_order_temporal_type_parameter_combinations>>{}(m);
}
