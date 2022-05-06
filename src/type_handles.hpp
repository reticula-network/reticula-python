#include <pybind11/pybind11.h>
#include "type_str/scalars.hpp"

namespace types {
  template <typename T>
  requires std::derived_from<
            pybind11::detail::make_caster<T>,
            pybind11::detail::type_caster_generic>
  pybind11::handle handle_for(const pybind11::module_&) {
    return pybind11::type::of<T>();
  }

  // Hack: pybind11::type::of<T> cannot handle non-generic types (int, float
  // etc.) see: https://github.com/pybind/pybind11/issues/2486
  template <typename T>
  pybind11::handle handle_for() {
    return pybind11::detail::get_type_handle(typeid(T), true);
  }
}
