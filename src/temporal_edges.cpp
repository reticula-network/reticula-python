#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl.h>
#include <fmt/format.h>

#include <dag/temporal_edges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_edges {
  void operator()(nb::module &m) {
    define_basic_edge_concept<dag::undirected_temporal_edge<VertT, TimeT>>(m)
      .def(nb::init<VertT, VertT, TimeT>(),
          "v1"_a, "v2"_a, "time"_a)
      .def(nb::init([](std::tuple<VertT, VertT, TimeT> t) {
              return dag::undirected_temporal_edge<VertT, TimeT>(
                  std::get<0>(t), std::get<1>(t), std::get<2>(t));
            }), "tuple"_a);

    nb::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT>,
      dag::undirected_temporal_edge<VertT, TimeT>>();

    define_basic_edge_concept<dag::directed_temporal_edge<VertT, TimeT>>(m)
      .def(nb::init<VertT, VertT, TimeT>(),
          "tail"_a, "head"_a, "time"_a)
      .def(nb::init([](std::tuple<VertT, VertT, TimeT> t) {
              return dag::directed_temporal_edge<VertT, TimeT>(
                  std::get<0>(t), std::get<1>(t), std::get<2>(t));
            }), "tuple"_a)
      .def("head",
          &dag::directed_temporal_edge<VertT, TimeT>::head)
      .def("tail",
          &dag::directed_temporal_edge<VertT, TimeT>::tail);

    nb::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT>,
      dag::directed_temporal_edge<VertT, TimeT>>();

    define_basic_edge_concept<
        dag::directed_delayed_temporal_edge<VertT, TimeT>>(m)
      .def(nb::init<VertT, VertT, TimeT, TimeT>(),
          "tail"_a, "head"_a, "cause_time"_a, "effect_time"_a)
      .def(nb::init([](std::tuple<VertT, VertT, TimeT, TimeT> t) {
              return dag::directed_delayed_temporal_edge<VertT, TimeT>(
                  std::get<0>(t), std::get<1>(t),
                  std::get<2>(t), std::get<3>(t));
            }), "tuple"_a)
      .def("head",
          &dag::directed_delayed_temporal_edge<VertT, TimeT>::head)
      .def("tail",
          &dag::directed_delayed_temporal_edge<VertT, TimeT>::tail);

    nb::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT, TimeT>,
      dag::directed_delayed_temporal_edge<VertT, TimeT>>();
  }
};

void declare_typed_temporal_edges(nb::module& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_edges>>,
      types::first_order_temporal_type_parameter_combinations>>{}(m);
}
