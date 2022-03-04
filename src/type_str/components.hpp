#ifndef SRC_TYPE_STR_COMPONENTS_HPP_
#define SRC_TYPE_STR_COMPONENTS_HPP_

#include <string>

#include <fmt/format.h>

#include <dag/components.hpp>

#include "common.hpp"
#include "scalars.hpp"
#include "edges.hpp"

// components
template <dag::network_vertex VertT>
struct type_str<dag::component<VertT>> {
    std::string operator()() {
        return fmt::format("component[{}]",
            type_str<VertT>{}());
    }
};

template <dag::network_vertex VertT>
struct type_str<dag::component_size<VertT>> {
    std::string operator()() {
        return fmt::format("component_size[{}]",
            type_str<VertT>{}());
    }
};

template <dag::network_vertex VertT>
struct type_str<dag::component_size_estimate<VertT>> {
    std::string operator()() {
        return fmt::format("component_size_estimate[{}]",
            type_str<VertT>{}());
    }
};

// Formatters


// dag::component is a range. We should make it ineligible for normal
// fmt::formatter defined for ranges to make our own. otherwise it'll
// get confused.
template <dag::network_vertex VertT>
struct fmt::is_range<dag::component<VertT>, char> : std::false_type {};

template <dag::network_vertex VertT>
struct fmt::formatter<dag::component<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::component<VertT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    std::size_t size = a.size();
    return fmt::format_to(
        ctx.out(),
        "<dag.{} of {} nodes: {{{}{}}})>",
        type_str<dag::component<VertT>>{}(), size,
        fmt::join(std::ranges::take_view{a, 10}, ", "),
        (size > 10) ? ", ..." : "");
  }
};

template <dag::network_vertex VertT>
struct fmt::formatter<dag::component_size<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::component_size<VertT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{} of {} nodes>",
        type_str<dag::component_size<VertT>>{}(), a.size());
  }
};

template <dag::network_vertex VertT>
struct fmt::formatter<dag::component_size_estimate<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::component_size_estimate<VertT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{} of ~{:1.2e}±1.1\% nodes>",
        type_str<dag::component_size_estimate<VertT>>{}(), a.size_estimate());
  }
};

#endif  // SRC_TYPE_STR_COMPONENTS_HPP_
