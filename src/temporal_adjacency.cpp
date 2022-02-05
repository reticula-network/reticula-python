#include <pybind11/pybind11.h>
#include <dag/dag.hpp>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <dag::temporal_edge EdgeT>
struct declare_temporal_adjacency_class {
  void operator()(py::module &m) {
    using Simple = dag::temporal_adjacency::simple<EdgeT>;
    py::class_<Simple>(m,
        type_str<Simple>{}().c_str())
      .def(py::init<>())
      .def("cutoff_time",
          &Simple::cutoff_time)
      .def("cutoff_dt",
          &Simple::cutoff_dt);

    using LWT = dag::temporal_adjacency::limited_waiting_time<EdgeT>;
    py::class_<LWT>(m,
        type_str<LWT>{}().c_str())
      .def(py::init<typename EdgeT::TimeType>(),
          "dt"_a)
      .def("cutoff_time",
          &LWT::cutoff_time)
      .def("cutoff_dt",
          &LWT::cutoff_dt);

    using Exp = dag::temporal_adjacency::exponential<EdgeT>;
    py::class_<Exp>(m,
        type_str<Exp>{}().c_str())
      .def(py::init<typename EdgeT::TimeType, std::size_t>(),
          "expected_dt"_a, "seed"_a)
      .def("cutoff_time",
          &Exp::cutoff_time)
      .def("cutoff_dt",
          &Exp::cutoff_dt);
  }
};

void declare_typed_temporal_adjacency_class(py::module& m) {
  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_adjacency_class>,
      types::first_order_temporal_edges>>{}(m);
}
