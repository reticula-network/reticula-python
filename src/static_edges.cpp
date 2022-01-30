#include <metal.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>
#include <dag/dag.hpp>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_static_edges {
  void operator()(py::module &m) {
    using Undirected = dag::undirected_edge<VertT>;
    py::class_<Undirected>(m, type_str<Undirected>{}().c_str())
      .def(py::init<VertT, VertT>())
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
      .def("__repr__", [](const Undirected& a) {
        return fmt::format("{}", a);
      });
    m.def("adjacent",
        py::overload_cast<
            const Undirected&,
            const Undirected&>(
          &dag::adjacent<VertT>),
            "edge1"_a, "edge2"_a);
    m.def("effect_lt",
        py::overload_cast<
            const Undirected&,
            const Undirected&>(
          &dag::effect_lt<VertT>), "edge1"_a, "edge2"_a);

    using Directed = dag::directed_edge<VertT>;
    py::class_<Directed>(m, type_str<Directed>{}().c_str())
      .def(py::init<VertT, VertT>(),
          "tail"_a, "head"_a)
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
          &dag::adjacent<VertT>),
            "edge1"_a, "edge2"_a);
    m.def("effect_lt",
        py::overload_cast<
            const Directed&,
            const Directed&>(
          &dag::effect_lt<VertT>),
            "edge1"_a, "edge2"_a);
  }
};


void declare_typed_static_edges(py::module& m) {
  // simple (first order) temporal edges
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_edges>,
      types::all_vert_types>>{}(m);
}
