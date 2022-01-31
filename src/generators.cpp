#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <dag/dag.hpp>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_generators {
  void operator()(py::module& m) {
    m.def(("square_grid_graph_"+type_str<VertT>{}()).c_str(),
        &dag::square_grid_graph<VertT>,
        "side"_a, "dims"_a, "periodic"_a = false,
        py::call_guard<py::gil_scoped_release>());
    m.def(("path_graph_"+type_str<VertT>{}()).c_str(),
        &dag::path_graph<VertT>,
        "size"_a, "periodic"_a = false,
        py::call_guard<py::gil_scoped_release>());
    m.def(("cycle_graph_"+type_str<VertT>{}()).c_str(),
        &dag::cycle_graph<VertT>,
        "size"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def(("regular_ring_lattice_"+type_str<VertT>{}()).c_str(),
        &dag::regular_ring_lattice<VertT>,
        "size"_a, "degree"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def(("complete_graph_"+type_str<VertT>{}()).c_str(),
        &dag::complete_graph<VertT>,
        "size"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_generators(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_generators>,
      types::current_build_types<
        types::integer_vert_types>>>{}(m);
}
