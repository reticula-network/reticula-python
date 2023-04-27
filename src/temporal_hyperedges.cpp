#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <fmt/format.h>

#include <reticula/temporal_hyperedges.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "common_edge_properties.hpp"
#include "metaclass.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT, typename TimeT>
struct declare_temporal_hyperedges {
  void operator()(py::module &m, PyObject* metaclass) {
    define_basic_edge_concept<
        reticula::undirected_temporal_hyperedge<VertT, TimeT>>(m, metaclass)
      .def(py::init<std::vector<VertT>, TimeT>(),
          "verts"_a, "time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init([](std::tuple<std::vector<VertT>, TimeT> t) {
            return reticula::undirected_temporal_hyperedge<VertT, TimeT>(
                    std::get<0>(t), std::get<1>(t));
            }),
        "tuple"_a,
        py::call_guard<py::gil_scoped_release>());

    py::implicitly_convertible<
      std::pair<std::vector<VertT>, TimeT>,
      reticula::undirected_temporal_hyperedge<VertT, TimeT>>();

    define_basic_edge_concept<
        reticula::directed_temporal_hyperedge<VertT, TimeT>>(m, metaclass)
      .def(py::init<std::vector<VertT>, std::vector<VertT>, TimeT>(),
          "tails"_a, "heads"_a, "time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init([](std::tuple<std::vector<VertT>, std::vector<VertT>,
                      TimeT> t) {
            return reticula::directed_temporal_hyperedge<VertT, TimeT>(
                    std::get<0>(t), std::get<1>(t), std::get<2>(t));
          }),
          "tuple"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("heads",
          &reticula::directed_temporal_hyperedge<VertT, TimeT>::heads,
          py::call_guard<py::gil_scoped_release>())
      .def("tails",
          &reticula::directed_temporal_hyperedge<VertT, TimeT>::tails,
          py::call_guard<py::gil_scoped_release>());

    py::implicitly_convertible<
      std::tuple<std::vector<VertT>, std::vector<VertT>, TimeT>,
      reticula::directed_temporal_hyperedge<VertT, TimeT>>();

    define_basic_edge_concept<
        reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>>(
            m, metaclass)
      .def(py::init<std::vector<VertT>, std::vector<VertT>, TimeT, TimeT>(),
          "tails"_a, "heads"_a, "cause_time"_a, "effect_time"_a,
          py::call_guard<py::gil_scoped_release>())
      .def(py::init([](std::tuple<std::vector<VertT>, std::vector<VertT>,
                      TimeT, TimeT> t) {
              return reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>(
                      std::get<0>(t), std::get<1>(t),
                      std::get<2>(t), std::get<3>(t));
            }),
          "tuple"_a,
          py::call_guard<py::gil_scoped_release>())
      .def("heads",
          &reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>::heads,
          py::call_guard<py::gil_scoped_release>())
      .def("tails",
          &reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>::tails,
          py::call_guard<py::gil_scoped_release>());

    py::implicitly_convertible<
      std::tuple<std::vector<VertT>, std::vector<VertT>, TimeT, TimeT>,
      reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>>();
  }
};

void declare_typed_temporal_hyperedges(py::module& m) {
  auto metaclass = common_metaclass("_reticula_ext.temporal_hyperedge_metaclass");

  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_temporal_hyperedges>>,
      types::first_order_temporal_type_parameter_combinations>>{}(
          m, (PyObject*)metaclass);
}
