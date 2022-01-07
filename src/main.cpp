#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>
#include <dag/dag.hpp>

#include "type_str.hpp"

namespace py = pybind11;

void declare_typed_static_edges(py::module& m);
void declare_typed_static_networks(py::module& m);

void declare_typed_temporal_edges(py::module& m);
void declare_typed_temporal_networks(py::module& m);
void declare_typed_generators(py::module& m);

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

PYBIND11_MODULE(dag_ext, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: cmake_example
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc";
    declare_typed_static_edges(m);
    declare_typed_static_networks(m);

    declare_typed_temporal_edges(m);
    declare_typed_temporal_networks(m);

    declare_typed_generators(m);
#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
