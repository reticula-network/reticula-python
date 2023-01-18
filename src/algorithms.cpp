#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <reticula/algorithms.hpp>

#include "type_str/edges.hpp"
#include "type_str/scalars.hpp"

#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename T>
struct declare_degree_sequence_algorithms {
  void operator()(py::module& m) {
    m.def("is_graphic",
        &reticula::is_graphic<std::vector<T>>,
        "degree_seq"_a,
        py::call_guard<py::gil_scoped_release>());

    m.def("is_digraphic",
        &reticula::is_digraphic<std::vector<std::pair<T, T>>>,
        "in_out_degree_seq"_a,
        py::call_guard<py::gil_scoped_release>());
  }
};

void declare_typed_assortativity_algorithms(py::module& m);
void declare_typed_degree_algorithms(py::module& m);
void declare_typed_basic_temporal_network_algorithms(py::module& m);
void declare_typed_density_algorithms(py::module& m);
void declare_typed_directed_connectivity_algorithms(py::module& m);
void declare_typed_temporal_adjacency_algorithms(py::module& m);
void declare_typed_undirected_connectivity_algorithms(py::module& m);

void declare_algorithms(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_degree_sequence_algorithms>,
        metal::list<uint64_t>>>{}(m);

  declare_typed_assortativity_algorithms(m);
  declare_typed_degree_algorithms(m);
  declare_typed_basic_temporal_network_algorithms(m);
  declare_typed_density_algorithms(m);
  declare_typed_directed_connectivity_algorithms(m);
  declare_typed_temporal_adjacency_algorithms(m);
  declare_typed_undirected_connectivity_algorithms(m);
}
