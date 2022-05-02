#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/stl_bind.h>

#include <dag/components.hpp>

#include "type_str/components.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename VertT>
struct declare_component_containers {
  void operator()(nb::module_ &m) {
    using Component = dag::component<VertT>;
    nb::bind_vector<
      std::vector<std::pair<VertT, Component>>>(m,
          fmt::format("vector_pair_{}_{}",
            python_type_str<VertT>(),
            python_type_str<Component>()).c_str());
    nb::bind_vector<
      std::vector<Component>>(m,
          fmt::format("vector_{}",
            python_type_str<Component>()).c_str());

    using ComponentSize = dag::component_size<VertT>;
    nb::bind_vector<
      std::vector<std::pair<VertT, ComponentSize>>>(m,
          fmt::format("vector_pair_{}_{}",
            python_type_str<VertT>(),
            python_type_str<ComponentSize>()).c_str());
    nb::bind_vector<
      std::vector<ComponentSize>>(m,
          fmt::format("vector_{}",
            python_type_str<ComponentSize>()).c_str());

    using ComponentSizeEstimate =
      dag::component_size_estimate<VertT>;
    nb::bind_vector<
      std::vector<std::pair<VertT, ComponentSizeEstimate>>>(m,
          fmt::format("vector_pair_{}_{}",
            python_type_str<VertT>(),
            python_type_str<ComponentSizeEstimate>()).c_str());
    nb::bind_vector<
      std::vector<ComponentSizeEstimate>>(m,
          fmt::format("vector_{}",
            python_type_str<ComponentSizeEstimate>()).c_str());
  }
};

void declare_typed_component_containers(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_component_containers>,
      types::all_vert_types>>{}(m);
}
