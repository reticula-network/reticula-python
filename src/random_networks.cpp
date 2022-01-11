#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <dag/dag.hpp>

#include "type_str.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT, std::uniform_random_bit_generator Gen>
struct declare_random_network_models {
  void operator()(py::module& m) {
    m.def(("gnp_random_graph_"+type_str<VertT>{}()).c_str(),
        &dag::gnp_random_graph<VertT, Gen>,
        "n"_a, "p"_a, "random_state"_a);

    m.def(("ba_random_graph_"+type_str<VertT>{}()).c_str(),
        &dag::ba_random_graph<VertT, Gen>,
        "n"_a, "m"_a, "random_state"_a);

    m.def(("random_regular_graph_"+type_str<VertT>{}()).c_str(),
        &dag::random_regular_graph<VertT, Gen>,
        "size"_a, "degree"_a, "random_state"_a);
  }
};

void declare_typed_random_networks(py::module& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_random_network_models>>,
      metal::cartesian<types::integer_vert_types, types::random_state_types>
    >>{}(m);
}
