#include <vector>
#include <unordered_map>

#include <random>

#include "../bind_core.hpp"

#include <reticula/operations.hpp>

#include "../type_utils.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <reticula::network_edge EdgeT, std::uniform_random_bit_generator Gen>
struct declare_vertex_occupation_algorithms {
  void operator()(nb::module_& m) {
    m.def("occupy_vertices",
        &reticula::occupy_vertices<
          EdgeT, std::unordered_map<
            typename EdgeT::VertexType, double,
            reticula::hash<typename EdgeT::VertexType>>, Gen>,
        "network"_a, "prob_map"_a, "random_state"_a, "default_prob"_a=0.0,
        nb::call_guard<nb::gil_scoped_release>());
    m.def("occupy_vertices",
        &reticula::occupy_vertices<
          EdgeT, std::function<double(typename EdgeT::VertexType)>, Gen>,
        "network"_a, "prob_func"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());

    m.def("uniformly_occupy_vertices",
        &reticula::uniformly_occupy_vertices<EdgeT, Gen>,
        "network"_a, "occupation_prob"_a, "random_state"_a,
        nb::call_guard<nb::gil_scoped_release>());
  }
};
}


void declare_typed_vertex_occupation_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_vertex_occupation_algorithms>>,
      metal::cartesian<
        types::all_edge_types,
        types::random_state_types>>>{}(m);
}
