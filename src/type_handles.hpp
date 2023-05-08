#include "bind_core.hpp"
#include "type_str/scalars.hpp"

namespace types {
  template <typename T>
  nanobind::handle handle_for() {
    return nanobind::type<T>();
  }
}
