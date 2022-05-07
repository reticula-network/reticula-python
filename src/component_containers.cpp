#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <reticula/components.hpp>

#include "type_str/components.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename VertT>
struct declare_component_containers {
  void operator()(py::module &m) {
    using Component = reticula::component<VertT>;
    py::bind_vector<
      std::vector<std::pair<VertT, Component>>>(m,
          fmt::format("vector_pair_{}_{}",
            python_type_str<VertT>(),
            python_type_str<Component>()).c_str());
    py::bind_vector<
      std::vector<Component>>(m,
          fmt::format("vector_{}",
            python_type_str<Component>()).c_str());

    using ComponentSize = reticula::component_size<VertT>;
    py::bind_vector<
      std::vector<std::pair<VertT, ComponentSize>>>(m,
          fmt::format("vector_pair_{}_{}",
            python_type_str<VertT>(),
            python_type_str<ComponentSize>()).c_str());
    py::bind_vector<
      std::vector<ComponentSize>>(m,
          fmt::format("vector_{}",
            python_type_str<ComponentSize>()).c_str());

    using ComponentSizeEstimate =
      reticula::component_size_estimate<VertT>;
    py::bind_vector<
      std::vector<std::pair<VertT, ComponentSizeEstimate>>>(m,
          fmt::format("vector_pair_{}_{}",
            python_type_str<VertT>(),
            python_type_str<ComponentSizeEstimate>()).c_str());
    py::bind_vector<
      std::vector<ComponentSizeEstimate>>(m,
          fmt::format("vector_{}",
            python_type_str<ComponentSizeEstimate>()).c_str());
  }
};

void declare_typed_component_containers(py::module& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_component_containers>,
      types::all_vert_types>>{}(m);
}
