#ifndef SRC_TYPE_STR_DISTRIBUTIONS_HPP_
#define SRC_TYPE_STR_DISTRIBUTIONS_HPP_

#include <random>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <reticula/distributions.hpp>

#include "common.hpp"
#include "scalars.hpp"

template <std::integral ResultType>
struct type_str<std::geometric_distribution<ResultType>> {
  std::string operator()() {
      return fmt::format("geometric_distribution[{}]",
              type_str<ResultType>{}());
  }
};

template <std::floating_point ResultType>
struct type_str<std::exponential_distribution<ResultType>> {
  std::string operator()() {
      return fmt::format("exponential_distribution[{}]",
              type_str<ResultType>{}());
  }
};

template <std::floating_point ResultType>
struct type_str<reticula::power_law_with_specified_mean<ResultType>> {
  std::string operator()() {
      return fmt::format("power_law_with_specified_mean[{}]",
              type_str<ResultType>{}());
  }
};

template <std::floating_point ResultType>
struct type_str<reticula::residual_power_law_with_specified_mean<ResultType>> {
  std::string operator()() {
      return fmt::format("residual_power_law_with_specified_mean[{}]",
              type_str<ResultType>{}());
  }
};

template <std::floating_point ResultType>
struct type_str<reticula::hawkes_univariate_exponential<ResultType>> {
  std::string operator()() {
      return fmt::format("hawkes_univariate_exponential[{}]",
              type_str<ResultType>{}());
  }
};

template <typename ResultType>
requires std::integral<ResultType> || std::floating_point<ResultType>
struct type_str<reticula::delta_distribution<ResultType>> {
  std::string operator()() {
      return fmt::format("delta_distribution[{}]",
              type_str<ResultType>{}());
  }
};

template <std::integral ResultType>
struct fmt::formatter<std::geometric_distribution<ResultType>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const std::geometric_distribution<ResultType>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(ctx.out(), "{}(p={})",
        type_str<std::geometric_distribution<ResultType>>{}(), a.p());
  }
};

template <std::floating_point ResultType>
struct fmt::formatter<std::exponential_distribution<ResultType>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const std::exponential_distribution<ResultType>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(ctx.out(), "{}(lambda={})",
        type_str<std::exponential_distribution<ResultType>>{}(), a.lambda());
  }
};

template <std::floating_point ResultType>
struct fmt::formatter<reticula::power_law_with_specified_mean<ResultType>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::power_law_with_specified_mean<ResultType>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(ctx.out(), "{}(exponent={}, mean={})",
        type_str<reticula::power_law_with_specified_mean<ResultType>>{}(),
        a.exponent(), a.mean());
  }
};

template <std::floating_point ResultType>
struct fmt::formatter<
        reticula::residual_power_law_with_specified_mean<ResultType>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::residual_power_law_with_specified_mean<ResultType>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(ctx.out(), "{}(exponent={}, mean={})",
        type_str<
          reticula::residual_power_law_with_specified_mean<ResultType>>{}(),
        a.exponent(), a.mean());
  }
};

template <std::floating_point ResultType>
struct fmt::formatter<reticula::hawkes_univariate_exponential<ResultType>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const reticula::hawkes_univariate_exponential<ResultType>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(ctx.out(), "{}(mu={}, alpha={}, theta={}, phi={})",
        type_str<reticula::hawkes_univariate_exponential<ResultType>>{}(),
        a.mu(), a.alpha(), a.theta(), a.phi());
  }
};

template <typename ResultType>
struct fmt::formatter<reticula::delta_distribution<ResultType>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const reticula::delta_distribution<ResultType>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(ctx.out(), "{}(mean={})",
        type_str<reticula::delta_distribution<ResultType>>{}(), a.mean());
  }
};

#endif  // SRC_TYPE_STR_DISTRIBUTIONS_HPP_
