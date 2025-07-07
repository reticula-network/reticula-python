#include <reticula/network_concepts.hpp>

#include "bind_core.hpp"
#include "nanobind/operators.h"
#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename EdgeT>
nb::class_<EdgeT> define_basic_edge_concept(nb::module_& m) {
  nb::class_<EdgeT> cls(m, python_type_str<EdgeT>().c_str());

  cls.def(nb::init<EdgeT>(),
        "edge"_a,
        nb::call_guard<nb::gil_scoped_release>())
    .def("mutated_verts",
        &EdgeT::mutated_verts,
        nb::call_guard<nb::gil_scoped_release>())
    .def("mutator_verts",
        &EdgeT::mutator_verts,
        nb::call_guard<nb::gil_scoped_release>())
    .def("incident_verts",
        &EdgeT::incident_verts,
        nb::call_guard<nb::gil_scoped_release>())
    .def("is_incident",
        &EdgeT::is_incident,
        "vert"_a,
        nb::call_guard<nb::gil_scoped_release>())
    .def("is_in_incident",
        &EdgeT::is_in_incident,
        "vert"_a,
        nb::call_guard<nb::gil_scoped_release>())
    .def("is_out_incident",
        &EdgeT::is_out_incident,
        "vert"_a,
        nb::call_guard<nb::gil_scoped_release>())
    .def(nb::self == nb::self,
        nb::call_guard<nb::gil_scoped_release>())
    .def(nb::self != nb::self,
        nb::call_guard<nb::gil_scoped_release>())
    .def(nb::self < nb::self,
        nb::call_guard<nb::gil_scoped_release>())
    .def(nb::hash(nb::self),
        nb::call_guard<nb::gil_scoped_release>())
    .def("__copy__", [](const EdgeT& self) {
        return EdgeT(self);
    }).def("__deepcopy__", [](const EdgeT& self, nb::dict) {
        return EdgeT(self);
    }, "memo"_a)
    .def("__repr__", [](const EdgeT& a) {
      return fmt::format("{}", a);
    }).def_static("__class_repr__", []() {
      return fmt::format("<class '{}'>", type_str<EdgeT>{}());
    }).def_static("__class_name__", []() {
      return type_str<EdgeT>{}();
    }).def_static("vertex_type", []() {
      return types::handle_for<typename EdgeT::VertexType>();
    });

  using VertT = typename EdgeT::VertexType;
  if constexpr (reticula::temporal_network_edge<EdgeT>) {
    using TimeT = typename EdgeT::TimeType;
    cls.def("cause_time",
          &EdgeT::cause_time,
          nb::call_guard<nb::gil_scoped_release>())
    .def("effect_time",
          &EdgeT::effect_time,
          nb::call_guard<nb::gil_scoped_release>())
    .def("static_projection",
          &EdgeT::static_projection,
          nb::call_guard<nb::gil_scoped_release>())
    .def_static("static_projection_type", []() {
        return types::handle_for<typename EdgeT::StaticProjectionType>();
      })
    .def_static("time_type", []() {
      return types::handle_for<typename EdgeT::TimeType>();
    });

    m.def("adjacent",
      nb::overload_cast<
          const EdgeT&, const EdgeT&>(&reticula::adjacent<VertT, TimeT>),
        "edge1"_a, "edge2"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("effect_lt",
      nb::overload_cast<
          const EdgeT&, const EdgeT&>(&reticula::effect_lt<VertT, TimeT>),
        "edge1"_a, "edge2"_a,
        nb::call_guard<nb::gil_scoped_release>());
  } else {
    m.def("adjacent",
      nb::overload_cast<
          const EdgeT&, const EdgeT&>(&reticula::adjacent<VertT>),
          "edge1"_a, "edge2"_a,
          nb::call_guard<nb::gil_scoped_release>());
    m.def("effect_lt",
      nb::overload_cast<const EdgeT&, const EdgeT&>(
        &reticula::effect_lt<VertT>),
      "edge1"_a, "edge2"_a,
      nb::call_guard<nb::gil_scoped_release>());
  }

  m.def(fmt::format("is_network_edge_{}",
            python_type_str<EdgeT>()).c_str(),
          []{ return reticula::network_edge<EdgeT>; });
  m.def(fmt::format("is_static_edge_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::static_network_edge<EdgeT>; });
  m.def(fmt::format("is_temporal_edge_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::temporal_network_edge<EdgeT>; });
  m.def(fmt::format("is_instantaneous_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::is_instantaneous_v<EdgeT>; });
  m.def(fmt::format("is_undirected_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::is_undirected_v<EdgeT>; });
  m.def(fmt::format("is_directed_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::is_directed_v<EdgeT>; });
  m.def(fmt::format("is_dyadic_{}",
              python_type_str<EdgeT>()).c_str(),
          []{ return reticula::is_dyadic_v<EdgeT>; });


  m.def("is_network_edge",
          [](const EdgeT&){ return reticula::network_edge<EdgeT>; });
  m.def("is_static_edge",
          [](const EdgeT&){ return reticula::static_network_edge<EdgeT>; });
  m.def("is_temporal_edge",
          [](const EdgeT&){ return reticula::temporal_network_edge<EdgeT>; });
  m.def("is_instantaneous",
          [](const EdgeT&){ return reticula::is_instantaneous_v<EdgeT>; });
  m.def("is_undirected",
          [](const EdgeT&){ return reticula::is_undirected_v<EdgeT>; });
  m.def("is_directed",
          [](const EdgeT&){ return reticula::is_directed_v<EdgeT>; });
  m.def("is_dyadic",
          [](const EdgeT&){ return reticula::is_dyadic_v<EdgeT>; });

  return cls;
}
