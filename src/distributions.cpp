#include <random>
#include <concepts>

#include <pybind11/pybind11.h>
#include <reticula/distributions.hpp>

#include "type_str/distributions.hpp"
#include "type_utils.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

template <std::integral ResultType>
struct declare_integral_distributions {
  void operator()(py::module& m) {
    py::class_<std::geometric_distribution<ResultType>>(
        m, python_type_str<std::geometric_distribution<ResultType>>().c_str())
      .def(py::init<double>(), "p"_a)
      .def("p", &std::geometric_distribution<ResultType>::p)
      .def("__repr__", [](const std::geometric_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      });

    py::class_<reticula::delta_distribution<ResultType>>(m,
        python_type_str<reticula::delta_distribution<ResultType>>().c_str())
      .def(py::init<ResultType>(), "mean"_a)
      .def("mean", &reticula::delta_distribution<ResultType>::mean)
      .def("__repr__", [](
            const reticula::delta_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      });
  }
};

template <std::floating_point ResultType>
struct declare_floating_point_distributions {
  void operator()(py::module& m) {
    py::class_<std::exponential_distribution<ResultType>>(
        m, python_type_str<std::exponential_distribution<ResultType>>().c_str())
      .def(py::init<ResultType>(), "lambda"_a)
      .def("lambda", &std::exponential_distribution<ResultType>::lambda)
      .def("__repr__", [](
            const std::exponential_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      });

    py::class_<reticula::power_law_with_specified_mean<ResultType>>(m,
        python_type_str<
          reticula::power_law_with_specified_mean<ResultType>>().c_str())
      .def(py::init<ResultType, ResultType>(), "exponent"_a, "mean"_a)
      .def("exponent",
          &reticula::power_law_with_specified_mean<ResultType>::exponent)
      .def("mean",
          &reticula::power_law_with_specified_mean<ResultType>::mean)
      .def("__repr__", [](
            const reticula::power_law_with_specified_mean<ResultType>& a) {
        return fmt::format("{}", a);
      });

    py::class_<reticula::residual_power_law_with_specified_mean<ResultType>>(m,
        python_type_str<
          reticula::residual_power_law_with_specified_mean<
            ResultType>>().c_str())
      .def(py::init<ResultType, ResultType>(), "exponent"_a, "mean"_a)
      .def("exponent",
          &reticula::residual_power_law_with_specified_mean<
            ResultType>::exponent)
      .def("mean",
          &reticula::residual_power_law_with_specified_mean<ResultType>::mean)
      .def("__repr__", [](
            const reticula::residual_power_law_with_specified_mean<
              ResultType>& a) {
        return fmt::format("{}", a);
      });

    py::class_<reticula::hawkes_univariate_exponential<ResultType>>(m,
        python_type_str<
          reticula::hawkes_univariate_exponential<ResultType>>().c_str())
      .def(py::init<ResultType, ResultType, ResultType, ResultType>(),
          "mu"_a, "alpha"_a, "theta"_a, "phi"_a = ResultType{})
      .def("mu",
          &reticula::hawkes_univariate_exponential<ResultType>::mu)
      .def("alpha",
          &reticula::hawkes_univariate_exponential<ResultType>::alpha)
      .def("theta",
          &reticula::hawkes_univariate_exponential<ResultType>::theta)
      .def("phi",
          &reticula::hawkes_univariate_exponential<ResultType>::phi)
      .def("__repr__", [](
            const reticula::hawkes_univariate_exponential<ResultType>& a) {
        return fmt::format("{}", a);
      });

    py::class_<reticula::delta_distribution<ResultType>>(m,
        python_type_str<reticula::delta_distribution<ResultType>>().c_str())
      .def(py::init<ResultType>(), "mean"_a)
      .def("mean", &reticula::delta_distribution<ResultType>::mean)
      .def("__repr__", [](
            const reticula::delta_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      });
  }
};

void declare_typed_distributions(py::module& m) {
  using scalar_types = types::unique<metal::join<
    types::time_types, types::simple_vert_types>>;

  using integral_types = metal::copy_if<scalar_types,
        metal::trait<std::is_integral>>;
  types::run_each<
    metal::transform<
      metal::lambda<declare_integral_distributions>,
      integral_types>>{}(m);

  using floating_types = metal::copy_if<scalar_types,
        metal::trait<std::is_floating_point>>;
  types::run_each<
    metal::transform<
      metal::lambda<declare_floating_point_distributions>,
      floating_types>>{}(m);
}
