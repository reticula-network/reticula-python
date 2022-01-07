#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>
#include <dag/dag.hpp>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_edges {
  void operator()(py::module &m) {
    using UndirectedTemporal = dag::undirected_temporal_edge<VertT, TimeT>;
    py::class_<UndirectedTemporal>(m, type_str<UndirectedTemporal>{}().c_str())
      .def(py::init<VertT, VertT, TimeT>())
      .def("mutated_verts",   &UndirectedTemporal::mutated_verts)
      .def("mutator_verts",   &UndirectedTemporal::mutator_verts)
      .def("incident_verts",  &UndirectedTemporal::incident_verts)
      .def("is_incident",     &UndirectedTemporal::is_incident, "vert"_a)
      .def("is_in_incident",  &UndirectedTemporal::is_in_incident, "vert"_a)
      .def("is_out_incident", &UndirectedTemporal::is_out_incident, "vert"_a)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def("__repr__", [](const UndirectedTemporal& a) {
        return fmt::format("{}", a);
      });
    m.def("adjacent",
        py::overload_cast<
            const UndirectedTemporal&,
            const UndirectedTemporal&>(
          &dag::adjacent<VertT, TimeT>), "edge1"_a, "edge2"_a);
    m.def("effect_lt",
        py::overload_cast<
            const UndirectedTemporal&,
            const UndirectedTemporal&>(
          &dag::effect_lt<VertT, TimeT>), "edge1"_a, "edge2"_a);

    using DirectedTemporal = dag::directed_temporal_edge<VertT, TimeT>;
    py::class_<DirectedTemporal>(m, type_str<DirectedTemporal>{}().c_str())
      .def(py::init<VertT, VertT, TimeT>())
      .def("mutated_verts",   &DirectedTemporal::mutated_verts)
      .def("mutator_verts",   &DirectedTemporal::mutator_verts)
      .def("incident_verts",  &DirectedTemporal::incident_verts)
      .def("is_incident",     &DirectedTemporal::is_incident, "vert"_a)
      .def("is_in_incident",  &DirectedTemporal::is_in_incident, "vert"_a)
      .def("is_out_incident", &DirectedTemporal::is_out_incident, "vert"_a)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def("__repr__", [](const DirectedTemporal& a) {
        return fmt::format("{}", a);
      });
    m.def("adjacent",
        py::overload_cast<
            const DirectedTemporal&,
            const DirectedTemporal&>(
          &dag::adjacent<VertT, TimeT>), "edge1"_a, "edge2"_a);
    m.def("effect_lt",
        py::overload_cast<
            const DirectedTemporal&,
            const DirectedTemporal&>(
          &dag::effect_lt<VertT, TimeT>), "edge1"_a, "edge2"_a);

    using DirectedDelayedTemporal =
      dag::directed_delayed_temporal_edge<VertT, TimeT>;
    py::class_<DirectedDelayedTemporal>(m,
        type_str<DirectedDelayedTemporal>{}().c_str())
      .def(py::init<VertT, VertT, TimeT, TimeT>())
      .def("mutated_verts",   &DirectedDelayedTemporal::mutated_verts)
      .def("mutator_verts",   &DirectedDelayedTemporal::mutator_verts)
      .def("incident_verts",  &DirectedDelayedTemporal::incident_verts)
      .def("is_incident",     &DirectedDelayedTemporal::is_incident, "vert"_a)
      .def("is_in_incident",  &DirectedDelayedTemporal::is_in_incident, "vert"_a)
      .def("is_out_incident", &DirectedDelayedTemporal::is_out_incident, "vert"_a)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def("__repr__", [](const DirectedDelayedTemporal& a) {
        return fmt::format("{}", a);
      });
    m.def("adjacent",
        py::overload_cast<
            const DirectedDelayedTemporal&,
            const DirectedDelayedTemporal&>(
          &dag::adjacent<VertT, TimeT>), "edge1"_a, "edge2"_a);
    m.def("effect_lt",
        py::overload_cast<
            const DirectedDelayedTemporal&,
            const DirectedDelayedTemporal&>(
          &dag::effect_lt<VertT, TimeT>), "edge1"_a, "edge2"_a);
  }
};

void declare_typed_temporal_edges(py::module& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_edges>>,
      metal::cartesian<types::first_order_vert_types, types::time_types>
    >>{}(m);
}
