#include <unordered_map>
#include <functional>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::static_undirected_edge EdgeT>
struct declare_undirected_assortativity_algorithms {
  void operator()(py::module& m) {
    m.def("degree_assortativity",
          &reticula::degree_assortativity<EdgeT>,
          "network"_a,
          py::call_guard<py::gil_scoped_release>());

    m.def("attribute_assortativity",
          &reticula::attribute_assortativity<EdgeT,
            std::unordered_map<
              typename EdgeT::VertexType, double,
              reticula::hash<typename EdgeT::VertexType>>>,
          "network"_a,
          "attribute_map"_a,
          "default_value"_a,
          py::call_guard<py::gil_scoped_release>());
    m.def("attribute_assortativity",
          &reticula::attribute_assortativity<EdgeT,
            std::function<double(typename EdgeT::VertexType)>>,
          "network"_a,
          "attribute_fun"_a,
          py::call_guard<py::gil_scoped_release>());
  }
};

template <reticula::static_directed_edge EdgeT>
struct declare_directed_assortativity_algorithms {
  void operator()(py::module& m) {
    m.def("in_in_degree_assortativity",
          &reticula::in_in_degree_assortativity<EdgeT>,
          "network"_a,
          py::call_guard<py::gil_scoped_release>());
    m.def("in_out_degree_assortativity",
          &reticula::in_out_degree_assortativity<EdgeT>,
          "network"_a,
          py::call_guard<py::gil_scoped_release>());
    m.def("out_in_degree_assortativity",
          &reticula::out_in_degree_assortativity<EdgeT>,
          "network"_a,
          py::call_guard<py::gil_scoped_release>());
    m.def("out_out_degree_assortativity",
          &reticula::out_out_degree_assortativity<EdgeT>,
          "network"_a,
          py::call_guard<py::gil_scoped_release>());

    m.def("attribute_assortativity",
          &reticula::attribute_assortativity<EdgeT,
            std::unordered_map<
              typename EdgeT::VertexType, double,
              reticula::hash<typename EdgeT::VertexType>>,
            std::unordered_map<
              typename EdgeT::VertexType, double,
              reticula::hash<typename EdgeT::VertexType>>>,
          "network"_a,
          "mutator_attribute_map"_a,
          "mutated_attribute_map"_a,
          "mutator_default_value"_a,
          "mutated_default_value"_a,
          py::call_guard<py::gil_scoped_release>());
    m.def("attribute_assortativity",
          &reticula::attribute_assortativity<EdgeT,
            std::function<double(typename EdgeT::VertexType)>,
            std::function<double(typename EdgeT::VertexType)>>,
          "network"_a,
          "mutator_attribute_fun"_a,
          "mutated_attribute_fun"_a,
          py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_assortativity_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_undirected_assortativity_algorithms>,
      metal::join<
        types::first_order_undirected_edges,
        types::second_order_undirected_edges,
        types::first_order_undirected_hyperedges>>>{}(m);

  types::run_each<
    metal::transform<
      metal::lambda<declare_directed_assortativity_algorithms>,
      metal::join<
        types::first_order_directed_edges,
        types::second_order_directed_edges,
        types::first_order_directed_hyperedges>>>{}(m);
}
