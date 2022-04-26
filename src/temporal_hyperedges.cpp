#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <dag/temporal_hyperedges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_hyperedges {
  void operator()(py::module &m) {
    define_basic_edge_concept<
        dag::undirected_temporal_hyperedge<VertT, TimeT>>(m)
      .def(py::init<
          std::vector<VertT>,
          TimeT>(),
          "verts"_a, "time"_a);

    define_basic_edge_concept<
        dag::directed_temporal_hyperedge<VertT, TimeT>>(m)
      .def(py::init<
          std::vector<VertT>,
          std::vector<VertT>,
          TimeT>(),
          "tails"_a, "heads"_a, "time"_a)
      .def("heads",
          &dag::directed_temporal_hyperedge<VertT, TimeT>::heads)
      .def("tails",
          &dag::directed_temporal_hyperedge<VertT, TimeT>::tails);

    define_basic_edge_concept<
        dag::directed_delayed_temporal_hyperedge<VertT, TimeT>>(m)
      .def(py::init<
          std::vector<VertT>,
          std::vector<VertT>,
          TimeT, TimeT>(),
          "tails"_a, "heads"_a, "cause_time"_a, "effect_time"_a)
      .def("heads",
          &dag::directed_delayed_temporal_hyperedge<VertT, TimeT>::heads)
      .def("tails",
          &dag::directed_delayed_temporal_hyperedge<VertT, TimeT>::tails);
  }
};

void declare_typed_temporal_hyperedges(py::module& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_hyperedges>>,
      types::first_order_temporal_type_parameter_combinations>>{}(m);
}
