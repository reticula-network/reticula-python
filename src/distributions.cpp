#include <random>
#include <concepts>
#include <limits>

#include "bind_core.hpp"
#include <reticula/distributions.hpp>

#include "type_str/distributions.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <std::integral ResultType>
struct declare_integral_distributions {
  void operator()(nb::module_& m) {
    nb::class_<std::geometric_distribution<ResultType>>(
        m, python_type_str<std::geometric_distribution<ResultType>>().c_str())
      .def(nb::init<double>(), "p"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("p", &std::geometric_distribution<ResultType>::p,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](const std::geometric_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>",
            type_str<std::geometric_distribution<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<std::geometric_distribution<ResultType>>{}();
      });

    nb::class_<reticula::delta_distribution<ResultType>>(m,
        python_type_str<reticula::delta_distribution<ResultType>>().c_str())
      .def(nb::init<ResultType>(), "mean"_a)
      .def("mean", &reticula::delta_distribution<ResultType>::mean,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](
            const reticula::delta_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>",
          type_str<reticula::delta_distribution<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<reticula::delta_distribution<ResultType>>{}();
      });

    nb::class_<std::uniform_int_distribution<ResultType>>(m,
        python_type_str<std::uniform_int_distribution<ResultType>>().c_str())
      .def(nb::init<ResultType, ResultType>(),
          "a"_a, "b"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("a", &std::uniform_int_distribution<ResultType>::a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("b", &std::uniform_int_distribution<ResultType>::b,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](
            const std::uniform_int_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>",
            type_str<std::uniform_int_distribution<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<std::uniform_int_distribution<ResultType>>{}();
      });
  }
};

template <std::floating_point ResultType>
struct declare_floating_point_distributions {
  void operator()(nb::module_& m) {
    nb::class_<std::exponential_distribution<ResultType>>(
        m, python_type_str<std::exponential_distribution<ResultType>>().c_str())
      .def(nb::init<ResultType>(), "lmbda"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("lmbda", &std::exponential_distribution<ResultType>::lambda,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](
            const std::exponential_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>",
            type_str<std::exponential_distribution<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<std::exponential_distribution<ResultType>>{}();
      });

    nb::class_<reticula::power_law_with_specified_mean<ResultType>>(m,
        python_type_str<
          reticula::power_law_with_specified_mean<ResultType>>().c_str())
      .def(nb::init<ResultType, ResultType>(),
          "exponent"_a, "mean"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("exponent",
          &reticula::power_law_with_specified_mean<ResultType>::exponent,
          nb::call_guard<nb::gil_scoped_release>())
      .def("mean",
          &reticula::power_law_with_specified_mean<ResultType>::mean,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](
            const reticula::power_law_with_specified_mean<ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<
          reticula::power_law_with_specified_mean<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<
          reticula::power_law_with_specified_mean<ResultType>>{}();
      });

    nb::class_<reticula::residual_power_law_with_specified_mean<ResultType>>(m,
        python_type_str<
          reticula::residual_power_law_with_specified_mean<
            ResultType>>().c_str())
      .def(nb::init<ResultType, ResultType>(),
          "exponent"_a, "mean"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("exponent",
          &reticula::residual_power_law_with_specified_mean<
            ResultType>::exponent,
          nb::call_guard<nb::gil_scoped_release>())
      .def("mean",
          &reticula::residual_power_law_with_specified_mean<ResultType>::mean,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](
            const reticula::residual_power_law_with_specified_mean<
              ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<
          reticula::residual_power_law_with_specified_mean<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<
          reticula::residual_power_law_with_specified_mean<ResultType>>{}();
      });

    nb::class_<reticula::hawkes_univariate_exponential<ResultType>>(m,
        python_type_str<
          reticula::hawkes_univariate_exponential<ResultType>>().c_str())
      .def(nb::init<ResultType, ResultType, ResultType, ResultType>(),
          "mu"_a, "alpha"_a, "theta"_a, "phi"_a = ResultType{},
          nb::call_guard<nb::gil_scoped_release>())
      .def("mu",
          &reticula::hawkes_univariate_exponential<ResultType>::mu,
          nb::call_guard<nb::gil_scoped_release>())
      .def("alpha",
          &reticula::hawkes_univariate_exponential<ResultType>::alpha,
          nb::call_guard<nb::gil_scoped_release>())
      .def("theta",
          &reticula::hawkes_univariate_exponential<ResultType>::theta,
          nb::call_guard<nb::gil_scoped_release>())
      .def("phi",
          &reticula::hawkes_univariate_exponential<ResultType>::phi,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](
            const reticula::hawkes_univariate_exponential<ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>", type_str<
          reticula::hawkes_univariate_exponential<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<reticula::hawkes_univariate_exponential<ResultType>>{}();
      });

    nb::class_<reticula::delta_distribution<ResultType>>(m,
        python_type_str<reticula::delta_distribution<ResultType>>().c_str())
      .def(nb::init<ResultType>(), "mean"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("mean", &reticula::delta_distribution<ResultType>::mean,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](
            const reticula::delta_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>",
            type_str<reticula::delta_distribution<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<reticula::delta_distribution<ResultType>>{}();
      });

    nb::class_<std::uniform_real_distribution<ResultType>>(m,
        python_type_str<std::uniform_real_distribution<ResultType>>().c_str())
      .def(nb::init<ResultType, ResultType>(),
          "a"_a, "b"_a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("a", &std::uniform_real_distribution<ResultType>::a,
          nb::call_guard<nb::gil_scoped_release>())
      .def("b", &std::uniform_real_distribution<ResultType>::b,
          nb::call_guard<nb::gil_scoped_release>())
      .def("__repr__", [](
            const std::uniform_real_distribution<ResultType>& a) {
        return fmt::format("{}", a);
      }).def_static("__class_repr__", []() {
        return fmt::format("<class '{}'>",
          type_str<std::uniform_real_distribution<ResultType>>{}());
      })
      .def_static("__class_name__", []() {
        return type_str<std::uniform_real_distribution<ResultType>>{}();
      });
  }
};

void declare_typed_distributions(nb::module_& m) {
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
