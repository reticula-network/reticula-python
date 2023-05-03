#include "bind_core.hpp"
#include <nanobind/operators.h>

#include <reticula/generators.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT>
struct declare_generators {
  void operator()(nb::module_& m) {
    m.def(("square_grid_graph_"+python_type_str<VertT>()).c_str(),
        &reticula::square_grid_graph<VertT>,
        "side"_a, "dims"_a, "periodic"_a = false,
        nb::call_guard<nb::gil_scoped_release>());
    m.def(("path_graph_"+python_type_str<VertT>()).c_str(),
        &reticula::path_graph<VertT>,
        "size"_a, "periodic"_a = false,
        nb::call_guard<nb::gil_scoped_release>());
    m.def(("cycle_graph_"+python_type_str<VertT>()).c_str(),
        &reticula::cycle_graph<VertT>,
        "size"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def(("regular_ring_lattice_"+python_type_str<VertT>()).c_str(),
        &reticula::regular_ring_lattice<VertT>,
        "size"_a, "degree"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def(("complete_graph_"+python_type_str<VertT>()).c_str(),
        &reticula::complete_graph<VertT>,
        "size"_a,
        nb::call_guard<nb::gil_scoped_release>());
    m.def(("complete_directed_graph_"+python_type_str<VertT>()).c_str(),
        &reticula::complete_directed_graph<VertT>,
        "size"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};

void declare_typed_generators(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_generators>,
      types::integer_vert_types>>{}(m);
}
