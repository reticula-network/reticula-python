#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <dag/io.hpp>

#include "type_str/edges.hpp"

#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <dag::network_edge EdgeT>
struct declare_io_functions {
  void operator()(py::module& m) {
    m.def(fmt::format("read_edgelist_{}", python_type_str<EdgeT>()).c_str(),
        [](const std::string& path, char delimiter, char quote) {
          return dag::read_edgelist<EdgeT>(path, delimiter, quote);
        }, "path"_a, "delimiter"_a = ' ', "quote"_a = '"',
        py::call_guard<py::gil_scoped_release>());
  }
};

using simple_temporal_type_parameter_combinations =
  metal::cartesian<types::simple_vert_types, types::time_types>;

void declare_typed_io_functions(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_io_functions>,
      metal::join<
        metal::transform<
          metal::lambda<dag::undirected_edge>,
          types::simple_vert_types>,
        metal::transform<
          metal::lambda<dag::directed_edge>,
          types::simple_vert_types>,
        metal::transform<
          metal::partial<
            metal::lambda<metal::apply>,
            metal::lambda<dag::undirected_temporal_edge>>,
          simple_temporal_type_parameter_combinations>,
        metal::transform<
          metal::partial<
            metal::lambda<metal::apply>,
            metal::lambda<dag::directed_temporal_edge>>,
          simple_temporal_type_parameter_combinations>,
        metal::transform<
          metal::partial<
            metal::lambda<metal::apply>,
            metal::lambda<dag::directed_delayed_temporal_edge>>,
          simple_temporal_type_parameter_combinations>>>>{}(m);
}
