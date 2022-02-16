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
      .def("linger",
          &Simple::linger)
      .def("maximum_linger",
          &Simple::maximum_linger);

    using LWT = dag::temporal_adjacency::limited_waiting_time<EdgeT>;
    py::class_<LWT>(m,
        type_str<LWT>{}().c_str())
      .def(py::init<typename EdgeT::TimeType>(),
          "dt"_a)
      .def("linger",
          &LWT::linger)
      .def("maximum_linger",
          &LWT::maximum_linger)
      .def("dt",
          &LWT::dt);

    if constexpr (std::is_floating_point_v<typename EdgeT::TimeType>) {
      using Exp = dag::temporal_adjacency::exponential<EdgeT>;
      py::class_<Exp>(m,
          type_str<Exp>{}().c_str())
        .def(py::init<typename EdgeT::TimeType, std::size_t>(),
            "rate"_a, "seed"_a)
        .def("linger",
            &Exp::linger)
        .def("maximum_linger",
            &Exp::maximum_linger)
        .def("rate",
            &Exp::rate);
    }

    if constexpr (std::is_integral_v<typename EdgeT::TimeType>) {
      using Geom = dag::temporal_adjacency::geometric<EdgeT>;
      py::class_<Geom>(m,
          type_str<Geom>{}().c_str())
        .def(py::init<double, std::size_t>(),
            "p"_a, "seed"_a)
        .def("linger",
            &Geom::linger)
        .def("maximum_linger",
            &Geom::maximum_linger)
        .def("p",
            &Geom::p);
    }
  }
};

void declare_typed_temporal_adjacency_class(py::module& m) {
  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_adjacency_class>,
      types::first_order_temporal_edges>>{}(m);
}
