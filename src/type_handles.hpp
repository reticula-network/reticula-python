#include "bind_core.hpp"
#include "type_str/scalars.hpp"

namespace types {
  // template <typename T>
  // requires std::derived_from<
  //           nanobind::detail::make_caster<T>,
  //           nanobind::detail::type_caster_base>
  // nanobind::handle handle_for(const nanobind::module_&) {
  //   return nanobind::type<T>();
  // }
  //
  // Hack: nanobind::type::of<T> cannot handle non-generic types (int, float
  // etc.) see: https://github.com/pybind/pybind11/issues/2486
  template <typename T>
  nanobind::handle handle_for() {
    return nanobind::type<T>();
    // return nanobind::get_type_handle(typeid(T), true);
  }
}
