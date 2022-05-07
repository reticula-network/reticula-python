#include <reticula/type_traits.hpp>
#include <reticula/network_concepts.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename EdgeT>
py::class_<EdgeT> define_basic_edge_concept(py::module &m) {
  py::class_<EdgeT> cls(m, python_type_str<EdgeT>().c_str());

  cls.def("mutated_verts",
        &EdgeT::mutated_verts)
    .def("mutator_verts",
        &EdgeT::mutator_verts)
    .def("incident_verts",
        &EdgeT::incident_verts)
    .def("is_incident",
        &EdgeT::is_incident,
        "vert"_a)
    .def("is_in_incident",
        &EdgeT::is_in_incident,
        "vert"_a)
    .def("is_out_incident",
        &EdgeT::is_out_incident,
        "vert"_a)
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def(py::self < py::self)
    .def(py::hash(py::self))
    .def("__repr__", [](const EdgeT& a) {
      return fmt::format("{}", a);
    })
    .def_static("vertex_type", []() {
      return types::handle_for<typename EdgeT::VertexType>();
    });

  using VertT = typename EdgeT::VertexType;
  if constexpr (reticula::temporal_edge<EdgeT>) {
    using TimeT = typename EdgeT::TimeType;
    cls.def("cause_time",
          &EdgeT::cause_time);
    cls.def("effect_time",
          &EdgeT::effect_time)
    .def_static("time_type", []() {
      return types::handle_for<typename EdgeT::TimeType>();
    });

    m.def("adjacent",
      py::overload_cast<
          const EdgeT&,
          const EdgeT&>(
        &reticula::adjacent<VertT, TimeT>),
          "edge1"_a, "edge2"_a);
    m.def("effect_lt",
      py::overload_cast<
          const EdgeT&,
          const EdgeT&>(
        &reticula::effect_lt<VertT, TimeT>),
          "edge1"_a, "edge2"_a);
  } else {
    m.def("adjacent",
      py::overload_cast<
          const EdgeT&,
          const EdgeT&>(
        &reticula::adjacent<VertT>),
          "edge1"_a, "edge2"_a);
    m.def("effect_lt",
      py::overload_cast<
          const EdgeT&,
          const EdgeT&>(
        &reticula::effect_lt<VertT>), "edge1"_a, "edge2"_a);
  }

  m.def(fmt::format("is_network_edge_{}",
            python_type_str<EdgeT>()).c_str(),
          []{ return reticula::network_edge<EdgeT>; });
  m.def(fmt::format("is_static_edge_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::static_edge<EdgeT>; });
  m.def(fmt::format("is_temporal_edge_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::temporal_edge<EdgeT>; });
  m.def(fmt::format("is_instantaneous_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::is_instantaneous_v<EdgeT>; });
  m.def(fmt::format("is_undirected_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::is_undirected_v<EdgeT>; });
  m.def(fmt::format("is_dyadic_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::is_dyadic_v<EdgeT>; });

  return cls;
}
