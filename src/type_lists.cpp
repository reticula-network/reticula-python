#include "bind_core.hpp"

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace {
namespace nb = nanobind;

template <typename T>
struct add_to_type_list {
  void operator()(nb::module_ &m, std::string list_name) {
    m.attr(list_name.c_str()).attr("append")(types::handle_for<T>());
  }
};
}

void declare_type_lists(nb::module_& m) {
  nb::setattr(m, "simple_vertex_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::simple_vert_types>>{}(m, "simple_vertex_types");

  nb::setattr(m, "first_order_vertex_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::first_order_vert_types>>{}(m, "first_order_vertex_types");

  nb::setattr(m, "integer_vertex_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::integer_vert_types>>{}(m, "integer_vertex_types");

  nb::setattr(m, "vertex_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::all_vert_types>>{}(m, "vertex_types");

  nb::setattr(m, "time_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::time_types>>{}(m, "time_types");

  nb::setattr(m, "edge_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::all_edge_types>>{}(m, "edge_types");

  nb::setattr(m, "temporal_edge_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::first_order_temporal_edges>>{}(m, "temporal_edge_types");


  using scalar_types = types::unique<metal::join<
    types::time_types, types::simple_vert_types>>;

  using integral_types = metal::copy_if<scalar_types,
        metal::trait<std::is_integral>>;
  nb::setattr(m, "integral_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      integral_types>>{}(m, "integral_types");

  using floating_types = metal::copy_if<scalar_types,
        metal::trait<std::is_floating_point>>;
  nb::setattr(m, "floating_point_types", nb::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      floating_types>>{}(m, "floating_point_types");
}
