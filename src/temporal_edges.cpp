#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <dag/temporal_edges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_edges {
  void operator()(py::module &m) {
    define_basic_edge_concept<dag::undirected_temporal_edge<VertT, TimeT>>(m)
      .def(py::init<VertT, VertT, TimeT>(),
          "v1"_a, "v2"_a, "time"_a);

    define_basic_edge_concept<dag::directed_temporal_edge<VertT, TimeT>>(m)
      .def(py::init<VertT, VertT, TimeT>(),
          "tail"_a, "head"_a, "time"_a)
      .def("head",
          &dag::directed_temporal_edge<VertT, TimeT>::head)
      .def("tail",
          &dag::directed_temporal_edge<VertT, TimeT>::tail);

    define_basic_edge_concept<
        dag::directed_delayed_temporal_edge<VertT, TimeT>>(m)
      .def(py::init<VertT, VertT, TimeT, TimeT>(),
          "tail"_a, "head"_a, "cause_time"_a, "effect_time"_a)
      .def("head",
          &dag::directed_delayed_temporal_edge<VertT, TimeT>::head)
      .def("tail",
          &dag::directed_delayed_temporal_edge<VertT, TimeT>::tail);
  }
};

void declare_typed_temporal_edges(py::module& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_edges>>,
      types::first_order_temporal_type_parameter_combinations>>{}(m);
}
