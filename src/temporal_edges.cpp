#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <reticula/temporal_edges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"
#include "metaclass.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_edges {
  void operator()(py::module &m, PyObject* metaclass) {
    define_basic_edge_concept<reticula::undirected_temporal_edge<VertT, TimeT>>(
        m, metaclass)
      .def(py::init<VertT, VertT, TimeT>(),
          "v1"_a, "v2"_a, "time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init([](std::tuple<VertT, VertT, TimeT> t) {
              return reticula::undirected_temporal_edge<VertT, TimeT>(
                  std::get<0>(t), std::get<1>(t), std::get<2>(t));
            }),
          "tuple"_a,
          py::call_guard<py::gil_scoped_release>());

    py::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT>,
      reticula::undirected_temporal_edge<VertT, TimeT>>();

    define_basic_edge_concept<reticula::directed_temporal_edge<VertT, TimeT>>(
        m, metaclass)
      .def(py::init<VertT, VertT, TimeT>(),
          "tail"_a, "head"_a, "time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init([](std::tuple<VertT, VertT, TimeT> t) {
              return reticula::directed_temporal_edge<VertT, TimeT>(
                  std::get<0>(t), std::get<1>(t), std::get<2>(t));
            }),
          "tuple"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("head",
          &reticula::directed_temporal_edge<VertT, TimeT>::head,
          py::call_guard<py::gil_scoped_release>())
      .def("tail",
          &reticula::directed_temporal_edge<VertT, TimeT>::tail,
          py::call_guard<py::gil_scoped_release>());

    py::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT>,
      reticula::directed_temporal_edge<VertT, TimeT>>();

    define_basic_edge_concept<
        reticula::directed_delayed_temporal_edge<VertT, TimeT>>(m, metaclass)
      .def(py::init<VertT, VertT, TimeT, TimeT>(),
          "tail"_a, "head"_a, "cause_time"_a, "effect_time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init([](std::tuple<VertT, VertT, TimeT, TimeT> t) {
              return reticula::directed_delayed_temporal_edge<VertT, TimeT>(
                  std::get<0>(t), std::get<1>(t),
                  std::get<2>(t), std::get<3>(t));
            }),
          "tuple"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("head",
          &reticula::directed_delayed_temporal_edge<VertT, TimeT>::head,
          py::call_guard<py::gil_scoped_release>())
      .def("tail",
          &reticula::directed_delayed_temporal_edge<VertT, TimeT>::tail,
          py::call_guard<py::gil_scoped_release>());

    py::implicitly_convertible<
      std::tuple<VertT, VertT, TimeT, TimeT>,
      reticula::directed_delayed_temporal_edge<VertT, TimeT>>();
  }
};

void declare_typed_temporal_edges(py::module& m) {
  auto metaclass = common_metaclass("temporal_edge_metaclass");

  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_edges>>,
      types::first_order_temporal_type_parameter_combinations>>{}(
          m, (PyObject*)metaclass);
}
