#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <dag/random_networks.hpp>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <dag::integer_vertex VertT, std::uniform_random_bit_generator Gen>
struct declare_random_network_models {
  void operator()(py::module& m) {
    m.def(("random_gnp_graph_"+python_type_str<VertT>()).c_str(),
        &dag::random_gnp_graph<VertT, Gen>,
        "n"_a, "p"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def(("random_barabasi_albert_graph_"+
          python_type_str<VertT>()).c_str(),
        &dag::random_barabasi_albert_graph<VertT, Gen>,
        "n"_a, "m"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def(("random_regular_graph_"+
          python_type_str<VertT>()).c_str(),
        &dag::random_regular_graph<VertT, Gen>,
        "size"_a, "degree"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def(("random_expected_degree_sequence_graph_"+
          python_type_str<VertT>()).c_str(),
        &dag::random_expected_degree_sequence_graph<
          VertT, std::vector<double>, Gen>,
        "weight_sequence"_a, "random_state"_a, "self_loops"_a = false,
        py::call_guard<py::gil_scoped_release>());

    m.def(("random_directed_expected_degree_sequence_graph_"+
          python_type_str<VertT>()).c_str(),
        &dag::random_directed_expected_degree_sequence_graph<
          VertT, std::vector<std::pair<double, double>>, Gen>,
        "in_out_weight_sequence"_a, "random_state"_a, "self_loops"_a = false,
        py::call_guard<py::gil_scoped_release>());

    m.def(("random_degree_sequence_graph_"+
          python_type_str<VertT>()).c_str(),
        &dag::random_degree_sequence_graph<
          VertT, std::vector<VertT>, Gen>,
        "degree_sequence"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def(("random_directed_degree_sequence_graph_"+
          python_type_str<VertT>()).c_str(),
        &dag::random_directed_degree_sequence_graph<
          VertT, std::vector<std::pair<VertT, VertT>>, Gen>,
        "in_out_degree_sequence"_a, "random_state"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def(("random_fully_mixed_temporal_network_"+
          python_type_str<VertT>()).c_str(),
        &dag::random_fully_mixed_temporal_network<VertT, Gen>,
        "size"_a, "rate"_a, "max_t"_a, "random_state"_a);
    m.def(("random_directed_fully_mixed_temporal_network_"+
          python_type_str<VertT>()).c_str(),
        &dag::random_directed_fully_mixed_temporal_network<VertT, Gen>,
        "size"_a, "rate"_a, "max_t"_a, "random_state"_a);
  }

};

void declare_typed_random_networks(py::module& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_random_network_models>>,
      metal::cartesian<
        types::integer_vert_types,
        types::random_state_types>>>{}(m);
}
