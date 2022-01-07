#include <metal.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>
#include <dag/dag.hpp>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;

template <typename VertT>
struct declare_static_edges {
  void operator()(py::module &m) {
    using Undirected = dag::undirected_edge<VertT>;
    py::class_<Undirected>(m, type_str<Undirected>{}().c_str())
      .def(py::init<VertT, VertT>())
      .def("mutated_verts",   &Undirected::mutated_verts)
      .def("mutator_verts",   &Undirected::mutator_verts)
      .def("incident_verts",  &Undirected::incident_verts)
      .def("is_incident",     &Undirected::is_incident)
      .def("is_in_incident",  &Undirected::is_in_incident)
      .def("is_out_incident", &Undirected::is_out_incident)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def("__repr__", [](const Undirected& a) {
        return fmt::format("{}", a);
      });

    using Directed = dag::directed_edge<VertT>;
    py::class_<Directed>(m, type_str<Directed>{}().c_str())
      .def(py::init<VertT, VertT>())
      .def("mutated_verts",   &Directed::mutated_verts)
      .def("mutator_verts",   &Directed::mutator_verts)
      .def("incident_verts",  &Directed::incident_verts)
      .def("is_incident",     &Directed::is_incident)
      .def("is_in_incident",  &Directed::is_in_incident)
      .def("is_out_incident", &Directed::is_out_incident)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def("__repr__", [](const Directed& a) {
        return fmt::format("{}", a);
      });
  }
};


void declare_typed_static_edges(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_edges>,
      types::simple_vert_types>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_static_edges>,
      types::simple_temporal_edges>>{}(m);

  /* types::run_each< */
  /*   metal::transform< */
  /*     metal::lambda<declare_static_edges>, */
  /*     types::simple_temporal_hyperedges>>{}(m); */
}
