#include <metal.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <reticula/static_edges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_static_edges {
  void operator()(py::module &m) {
    define_basic_edge_concept<reticula::undirected_edge<VertT>>(m)
      .def(py::init<VertT, VertT>(), "v1"_a, "v2"_a)
      .def(py::init([](std::tuple<VertT, VertT> t) {
            return reticula::undirected_edge<VertT>(
                std::get<0>(t), std::get<1>(t));
            }),
          "tuple"_a,
          py::call_guard<py::gil_scoped_release>());

    py::implicitly_convertible<
      std::tuple<VertT, VertT>,
      reticula::undirected_edge<VertT>>();

    define_basic_edge_concept<reticula::directed_edge<VertT>>(m)
      .def(py::init<VertT, VertT>(),
          "tail"_a, "head"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init([](std::tuple<VertT, VertT> t) {
            return reticula::directed_edge<VertT>(
                std::get<0>(t), std::get<1>(t));
            }),
          "tuple"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("head",
          &reticula::directed_edge<VertT>::head,
          py::call_guard<py::gil_scoped_release>())
      .def("tail",
          &reticula::directed_edge<VertT>::tail,
          py::call_guard<py::gil_scoped_release>());

    py::implicitly_convertible<
      std::tuple<VertT, VertT>,
      reticula::directed_edge<VertT>>();
  }
};


void declare_typed_static_edges(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_static_edges>,
      types::all_vert_types>>{}(m);
}
