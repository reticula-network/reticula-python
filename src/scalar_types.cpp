#include <nanobind/nanobind.h>
#include <nanobind/operators.h>

#include "type_str/scalars.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <typename T>
struct declare_scalar_types {
  void operator()(nb::module_ &m) {
    nb::class_<T>(m,
        python_type_str<T>().c_str());
  }
};

template<class seq>
using unique = metal::accumulate<
  metal::bind<
    metal::lambda<metal::if_>,
    metal::lambda<metal::contains>, metal::_1,
    metal::lambda<metal::append>>, metal::list<>, seq>;

void declare_typed_scalar(nb::module_& m) {
  using scalar_types = unique<metal::join<
    types::time_types, types::simple_vert_types>>;

  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_scalar_types>,
      metal::join<scalar_types, types::pair_vert_types>>>{}(m);
}
