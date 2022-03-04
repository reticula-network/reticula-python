#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "type_str/scalars.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <typename T>
struct declare_scalar_types {
  void operator()(py::module &m) {
    py::class_<T>(m,
        python_type_str<T>().c_str())
      .def("__repr__", [](const T& a) {
        return fmt::format("{}", a);
      });
  }
};

template<class seq>
using unique = metal::accumulate<
  metal::bind<
    metal::lambda<metal::if_>,
    metal::lambda<metal::contains>, metal::_1,
    metal::lambda<metal::append>>, metal::list<>, seq>;

void declare_typed_scalar(py::module& m) {
  using scalar_types = unique<metal::join<
    types::time_types, types::simple_vert_types>>;

  // declare network
  types::run_each<
    metal::transform<
      metal::lambda<declare_scalar_types>,
      scalar_types>>{}(m);
}
