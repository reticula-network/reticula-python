#include <nanobind/nanobind.h>
#include <dag/temporal_adjacency.hpp>

#include "type_str/temporal_adjacency.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <dag::temporal_edge EdgeT>
struct declare_temporal_adjacency_class {
  void operator()(nb::module &m) {
    using Simple = dag::temporal_adjacency::simple<EdgeT>;
    nb::class_<Simple>(m,
        python_type_str<Simple>().c_str())
      .def(nb::init<>())
      .def("linger",
          &Simple::linger)
      .def("maximum_linger",
          &Simple::maximum_linger);

    using LWT = dag::temporal_adjacency::limited_waiting_time<EdgeT>;
    nb::class_<LWT>(m,
        python_type_str<LWT>().c_str())
      .def(nb::init<typename EdgeT::TimeType>(),
          "dt"_a)
      .def("linger",
          &LWT::linger)
      .def("maximum_linger",
          &LWT::maximum_linger)
      .def("dt",
          &LWT::dt);

    if constexpr (std::is_floating_point_v<typename EdgeT::TimeType>) {
      using Exp = dag::temporal_adjacency::exponential<EdgeT>;
      nb::class_<Exp>(m,
          python_type_str<Exp>().c_str())
        .def(nb::init<typename EdgeT::TimeType, std::size_t>(),
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
      nb::class_<Geom>(m,
          python_type_str<Geom>().c_str())
        .def(nb::init<double, std::size_t>(),
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

void declare_typed_temporal_adjacency_class(nb::module& m) {
  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_adjacency_class>,
      types::first_order_temporal_edges>>{}(m);
}
