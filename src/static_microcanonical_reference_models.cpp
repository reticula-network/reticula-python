#include "bind_core.hpp"

#include <reticula/microcanonical_reference_models.hpp>

#include "type_utils.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <
  reticula::undirected_network_edge EdgeT,
  std::uniform_random_bit_generator Gen>
struct declare_static_mrrm_algorithms {
  void operator()(nb::module_& m) {
    m.def("degree_sequence_preserving_shuffling",
	nb::overload_cast<
            const reticula::network<EdgeT>&, Gen&>(
	  &reticula::mrrms::degree_sequence_preserving_shuffling<EdgeT, Gen>),
	"static_network"_a, "random_state"_a,
	nb::call_guard<nb::gil_scoped_release>());

    m.def("degree_sequence_preserving_shuffling",
	nb::overload_cast<
            const reticula::network<EdgeT>&, Gen&, std::size_t>(
	  &reticula::mrrms::degree_sequence_preserving_shuffling<EdgeT, Gen>),
	"static_network"_a, "random_state"_a,
	"rewirings"_a,
	nb::call_guard<nb::gil_scoped_release>());

    m.def("joint_degree_sequence_preserving_shuffling",
	nb::overload_cast<
            const reticula::network<EdgeT>&, Gen&>(
	  &reticula::mrrms::joint_degree_sequence_preserving_shuffling<
	    EdgeT, Gen>),
	"static_network"_a, "random_state"_a,
	nb::call_guard<nb::gil_scoped_release>());

    m.def("joint_degree_sequence_preserving_shuffling",
	nb::overload_cast<
            const reticula::network<EdgeT>&, Gen&, std::size_t>(
	  &reticula::mrrms::joint_degree_sequence_preserving_shuffling<
	    EdgeT, Gen>),
	"static_network"_a, "random_state"_a,
	"rewirings"_a,
	nb::call_guard<nb::gil_scoped_release>());
  }
};
}

void declare_typed_static_mrrm_algorithms(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<declare_static_mrrm_algorithms>>,
      metal::cartesian<
        metal::join<
          types::first_order_undirected_edges,
          types::second_order_undirected_edges>,
        types::random_state_types>>>{}(m);
}
