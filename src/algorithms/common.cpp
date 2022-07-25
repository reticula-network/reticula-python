#include <vector>
#include <unordered_map>

#include <random>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>

#include "../type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <reticula::network_edge EdgeT>
struct declare_common_network_algorithms {
  void operator()(py::module& m) {
    m.def("vertex_induced_subgraph",
        &reticula::vertex_induced_subgraph<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("vertex_induced_subgraph",
        &reticula::vertex_induced_subgraph<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("edge_induced_subgraph",
        &reticula::edge_induced_subgraph<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("edge_induced_subgraph",
        &reticula::edge_induced_subgraph<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());


    m.def("graph_union",
        &reticula::graph_union<EdgeT>,
        "g1"_a, "g2"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_edges",
        &reticula::with_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_edges",
        &reticula::with_edges<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("with_vertices",
        &reticula::with_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("with_vertices",
        &reticula::with_vertices<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("without_edges",
        &reticula::without_edges<
          EdgeT, std::vector<EdgeT>>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("without_edges",
        &reticula::without_edges<
          EdgeT, const reticula::component<EdgeT>&>,
        "network"_a, "edges"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("without_vertices",
        &reticula::without_vertices<
          EdgeT, std::vector<typename EdgeT::VertexType>>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
    m.def("without_vertices",
        &reticula::without_vertices<
          EdgeT, const reticula::component<typename EdgeT::VertexType>&>,
        "network"_a, "verts"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

template <reticula::network_edge EdgeT, std::uniform_random_bit_generator Gen>
struct declare_common_network_occupation_algorithms {
  void operator()(py::module& m) {
    m.def("occupy_edges",
        &reticula::occupy_edges<
          EdgeT, std::unordered_map<EdgeT, double, reticula::hash<EdgeT>>, Gen>,
        "network"_a, "prob_map"_a, "random_state"_a, "default_prob"_a=0.0,
        py::call_guard<py::gil_scoped_release>());
    m.def("occupy_edges",
        &reticula::occupy_edges<
          EdgeT, std::function<double(EdgeT)>, Gen>,
        "network"_a, "prob_func"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("uniformly_occupy_edges",
        &reticula::uniformly_occupy_edges<EdgeT, Gen>,
        "network"_a, "occupation_prob"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());


    m.def("occupy_vertices",
        &reticula::occupy_vertices<
          EdgeT, std::unordered_map<
            typename EdgeT::VertexType, double,
            reticula::hash<typename EdgeT::VertexType>>, Gen>,
        "network"_a, "prob_map"_a, "random_state"_a, "default_prob"_a=0.0,
        py::call_guard<py::gil_scoped_release>());
    m.def("occupy_vertices",
        &reticula::occupy_vertices<
          EdgeT, std::function<double(typename EdgeT::VertexType)>, Gen>,
        "network"_a, "prob_func"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("uniformly_occupy_vertices",
        &reticula::uniformly_occupy_vertices<EdgeT, Gen>,
        "network"_a, "occupation_prob"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_common_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_common_network_algorithms>,
      types::all_edge_types>>{}(m);

  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_common_network_occupation_algorithms>>,
      metal::cartesian<
        types::all_edge_types,
        types::random_state_types>>>{}(m);
}
