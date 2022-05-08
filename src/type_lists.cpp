#include <pybind11/pybind11.h>

#include "type_str/scalars.hpp"
#include "type_str/edges.hpp"
#include "type_utils.hpp"
#include "type_handles.hpp"

namespace py = pybind11;

template <typename T>
struct add_to_type_list {
  void operator()(py::module &m, std::string list_name) {
    m.attr(list_name.c_str()).attr("append")(types::handle_for<T>());
  }
};

void declare_type_lists(py::module& m) {
  m.add_object("simple_vertex_types", py::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::simple_vert_types>>{}(m, "simple_vertex_types");

  m.add_object("first_order_vertex_types", py::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::first_order_vert_types>>{}(m, "first_order_vertex_types");

  m.add_object("integer_vertex_types", py::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::integer_vert_types>>{}(m, "integer_vertex_types");

  m.add_object("vertex_types", py::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::all_vert_types>>{}(m, "vertex_types");

  m.add_object("time_types", py::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::time_types>>{}(m, "time_types");

  m.add_object("edge_types", py::list());
  types::run_each<
    metal::transform<
      metal::lambda<add_to_type_list>,
      types::all_edge_types>>{}(m, "edge_types");
}
