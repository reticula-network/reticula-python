#ifndef SRC_TYPE_STR_TEMPORAL_ADJACENCY_HPP_
#define SRC_TYPE_STR_TEMPORAL_ADJACENCY_HPP_

#include <string>
#include <fmt/format.h>

#include <reticula/temporal_adjacency.hpp>

#include "common.hpp"
#include "edges.hpp"

// temporal adjacency
template <reticula::temporal_network_edge EdgeT>
struct type_str<reticula::temporal_adjacency::simple<EdgeT>> {
  std::string operator()() {
      return fmt::format("simple[{}]",
              type_str<EdgeT>{}());
  }
};

template <reticula::temporal_network_edge EdgeT>
struct type_str<reticula::temporal_adjacency::limited_waiting_time<EdgeT>> {
  std::string operator()() {
      return fmt::format("limited_waiting_time[{}]",
              type_str<EdgeT>{}());
  }
};

template <reticula::temporal_network_edge EdgeT>
struct type_str<reticula::temporal_adjacency::exponential<EdgeT>> {
  std::string operator()() {
      return fmt::format("exponential[{}]",
              type_str<EdgeT>{}());
  }
};

template <reticula::temporal_network_edge EdgeT>
struct type_str<reticula::temporal_adjacency::geometric<EdgeT>> {
  std::string operator()() {
      return fmt::format("geometric[{}]",
              type_str<EdgeT>{}());
  }
};

// formatters
template <reticula::temporal_network_edge EdgeT>
struct fmt::formatter<reticula::temporal_adjacency::simple<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::temporal_adjacency::simple<EdgeT>& /* a */,
      FormatContext& ctx) const -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<temporal_adjacency.{}>",
        type_str<reticula::temporal_adjacency::simple<EdgeT>>{}());
  }
};


template <reticula::temporal_network_edge EdgeT>
struct fmt::formatter<reticula::temporal_adjacency::limited_waiting_time<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::temporal_adjacency::limited_waiting_time<EdgeT>& a,
      FormatContext& ctx) const -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<temporal_adjacency.{} dt={}>",
        type_str<reticula::temporal_adjacency::limited_waiting_time<EdgeT>>{}(), a.dt());
  }
};

template <reticula::temporal_network_edge EdgeT>
struct fmt::formatter<reticula::temporal_adjacency::exponential<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::temporal_adjacency::exponential<EdgeT>& a,
      FormatContext& ctx) const -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<temporal_adjacency.{} rate={}>",
        type_str<reticula::temporal_adjacency::exponential<EdgeT>>{}(), a.rate());
  }
};


template <reticula::temporal_network_edge EdgeT>
struct fmt::formatter<reticula::temporal_adjacency::geometric<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::temporal_adjacency::geometric<EdgeT>& a,
      FormatContext& ctx) const -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<temporal_adjacency.{} rate={}>",
        type_str<reticula::temporal_adjacency::geometric<EdgeT>>{}(), a.p());
  }
};

#endif  // SRC_TYPE_STR_TEMPORAL_ADJACENCY_HPP_
