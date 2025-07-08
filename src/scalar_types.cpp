#include "bind_core.hpp"
#include <nanobind/operators.h>
#include <fmt/format.h>

#include "type_str/scalars.hpp"
#include "type_utils.hpp"
#include "scalar_wrapper.hpp"

namespace {
namespace nb = nanobind;
using namespace nanobind::literals;

template <typename T>
struct declare_scalar_types {
  void operator()(nb::module_ &m) {
    nb::class_<scalar_wrapper<T>>(m,
        python_type_str<T>().c_str())
      .def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<T>{}());
      }).def_static("__class_name__", []() {
        return type_str<T>{}();
      });
  }
};
}

void declare_typed_scalar(nb::module_& m) {
  using scalar_types = types::unique<metal::join<
    types::time_types, types::simple_vert_types>>;

  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_scalar_types>,
      metal::join<scalar_types, types::pair_vert_types>>>{}(m);
}
