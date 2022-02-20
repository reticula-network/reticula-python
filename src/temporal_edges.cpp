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
    using Undirected = dag::undirected_temporal_edge<VertT, TimeT>;
    py::class_<Undirected>(m, type_str<Undirected>{}().c_str())
      .def(py::init<VertT, VertT, TimeT>(),
          "v1"_a, "v2"_a, "time"_a)
      .def("mutated_verts",
          &Undirected::mutated_verts)
      .def("mutator_verts",
          &Undirected::mutator_verts)
      .def("incident_verts",
          &Undirected::incident_verts)
      .def("is_incident",
          &Undirected::is_incident,
          "vert"_a)
      .def("is_in_incident",
          &Undirected::is_in_incident,
          "vert"_a)
      .def("is_out_incident",
          &Undirected::is_out_incident,
          "vert"_a)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def(py::hash(py::self))
      .def("__repr__", [](const Undirected& a) {
        return fmt::format("{}", a);
      });
    m.def("adjacent",
        py::overload_cast<
            const Undirected&,
            const Undirected&>(
          &dag::adjacent<VertT, TimeT>),
            "edge1"_a, "edge2"_a);
    m.def("effect_lt",
        py::overload_cast<
            const Undirected&,
            const Undirected&>(
          &dag::effect_lt<VertT, TimeT>),
            "edge1"_a, "edge2"_a);

    using Directed = dag::directed_temporal_edge<VertT, TimeT>;
    py::class_<Directed>(m, type_str<Directed>{}().c_str())
      .def(py::init<VertT, VertT, TimeT>(),
          "tail"_a, "head"_a, "time"_a)
      .def("mutated_verts",
          &Directed::mutated_verts)
      .def("mutator_verts",
          &Directed::mutator_verts)
      .def("head",
          &Directed::head)
      .def("tail",
          &Directed::tail)
      .def("incident_verts",
          &Directed::incident_verts)
      .def("is_incident",
          &Directed::is_incident,
          "vert"_a)
      .def("is_in_incident",
          &Directed::is_in_incident,
          "vert"_a)
      .def("is_out_incident",
          &Directed::is_out_incident,
          "vert"_a)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def("__repr__", [](const Directed& a) {
        return fmt::format("{}", a);
      });
    m.def("adjacent",
        py::overload_cast<
            const Directed&,
            const Directed&>(
          &dag::adjacent<VertT, TimeT>),
            "edge1"_a, "edge2"_a);
    m.def("effect_lt",
        py::overload_cast<
            const Directed&,
            const Directed&>(
          &dag::effect_lt<VertT, TimeT>),
            "edge1"_a, "edge2"_a);

    using DirectedDelayed =
      dag::directed_delayed_temporal_edge<VertT, TimeT>;
    py::class_<DirectedDelayed>(m,
        type_str<DirectedDelayed>{}().c_str())
      .def(py::init<VertT, VertT, TimeT, TimeT>(),
          "tail"_a, "head"_a, "cause_time"_a, "effect_time"_a)
      .def("mutated_verts",
          &DirectedDelayed::mutated_verts)
      .def("mutator_verts",
          &DirectedDelayed::mutator_verts)
      .def("head",
          &DirectedDelayed::head)
      .def("tail",
          &DirectedDelayed::tail)
      .def("incident_verts",
          &DirectedDelayed::incident_verts)
      .def("is_incident",
          &DirectedDelayed::is_incident,
          "vert"_a)
      .def("is_in_incident",
          &DirectedDelayed::is_in_incident,
          "vert"_a)
      .def("is_out_incident",
          &DirectedDelayed::is_out_incident,
          "vert"_a)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def("__repr__", [](const DirectedDelayed& a) {
        return fmt::format("{}", a);
      });
    m.def("adjacent",
        py::overload_cast<
            const DirectedDelayed&,
            const DirectedDelayed&>(
          &dag::adjacent<VertT, TimeT>),
            "edge1"_a, "edge2"_a);
    m.def("effect_lt",
        py::overload_cast<
            const DirectedDelayed&,
            const DirectedDelayed&>(
          &dag::effect_lt<VertT, TimeT>),
            "edge1"_a, "edge2"_a);
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
