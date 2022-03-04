#ifndef SRC_TYPE_STR_EDGES_HPP_
#define SRC_TYPE_STR_EDGES_HPP_

#include <string>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <dag/static_edges.hpp>
#include <dag/static_hyperedges.hpp>
#include <dag/temporal_edges.hpp>
#include <dag/temporal_hyperedges.hpp>

#include "common.hpp"
#include "scalars.hpp"

// static edge

template <typename VertT>
struct type_str<dag::undirected_edge<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_edge[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_edge<VertT>> {
    std::string operator()() {
        return fmt::format("directed_edge[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::undirected_hyperedge<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_hyperedge[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_hyperedge<VertT>> {
    std::string operator()() {
        return fmt::format("directed_hyperedge[{}]", type_str<VertT>{}());
    }
};

// temporal edge
template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_edge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_edge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_edge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_hyperedge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_hyperedge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_hyperedge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

// formatters

// static edges

template <dag::network_vertex VertT>
struct fmt::formatter<dag::undirected_edge<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const dag::undirected_edge<VertT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(), "<dag.{}({})>",
        type_str<dag::undirected_edge<VertT>>{}(),
        fmt::join(a.incident_verts(), ", "));
  }
};


template <dag::network_vertex VertT>
struct fmt::formatter<dag::directed_edge<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const dag::directed_edge<VertT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{}({}, {})>",
        type_str<dag::directed_edge<VertT>>{}(),
        a.tail(), a.head());
  }
};

template <dag::network_vertex VertT>
struct fmt::formatter<dag::undirected_hyperedge<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const dag::undirected_hyperedge<VertT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(), "<dag.{}({})>",
        type_str<dag::undirected_hyperedge<VertT>>{}(),
        fmt::join(a.incident_verts(), ", "));
  }
};


template <dag::network_vertex VertT>
struct fmt::formatter<dag::directed_hyperedge<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const dag::directed_hyperedge<VertT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{}({}, {})>",
        type_str<dag::directed_hyperedge<VertT>>{}(),
        a.tails(), a.heads());
  }
};

// temporal edges
template <dag::network_vertex VertT, typename TimeT>
struct fmt::formatter<dag::undirected_temporal_edge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::undirected_temporal_edge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(), "<dag.{}({}, t={})>",
        type_str<dag::undirected_temporal_edge<VertT, TimeT>>{}(),
        fmt::join(a.incident_verts(), ", "),
        a.effect_time());
  }
};

template <dag::network_vertex VertT, typename TimeT>
struct fmt::formatter<dag::directed_temporal_edge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::directed_temporal_edge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{}({}, {}, t={})>",
        type_str<dag::directed_temporal_edge<VertT, TimeT>>{}(),
        a.tail(), a.head(), a.effect_time());
  }
};

template <dag::network_vertex VertT, typename TimeT>
struct fmt::formatter<dag::directed_delayed_temporal_edge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::directed_delayed_temporal_edge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{}({}, {}, t_start={}, t_end={})>",
        type_str<dag::directed_delayed_temporal_edge<VertT, TimeT>>{}(),
        a.tail(), a.head(), a.cause_time(), a.effect_time());
  }
};

template <dag::network_vertex VertT, typename TimeT>
struct fmt::formatter<dag::undirected_temporal_hyperedge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::undirected_temporal_hyperedge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(), "<dag.{}({}, t={})>",
        type_str<dag::undirected_temporal_hyperedge<VertT, TimeT>>{}(),
        fmt::join(a.incident_verts(), ", "),
        a.effect_time());
  }
};

template <dag::network_vertex VertT, typename TimeT>
struct fmt::formatter<dag::directed_temporal_hyperedge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::directed_temporal_hyperedge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{}({}, {}, t={})>",
        type_str<dag::directed_temporal_hyperedge<VertT, TimeT>>{}(),
        a.tails(), a.heads(), a.effect_time());
  }
};

template <dag::network_vertex VertT, typename TimeT>
struct fmt::formatter<dag::directed_delayed_temporal_hyperedge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::directed_delayed_temporal_hyperedge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{}({}, {}, t_start={}, t_end={})>",
        type_str<dag::directed_delayed_temporal_hyperedge<VertT, TimeT>>{}(),
        a.tails(), a.heads(), a.cause_time(), a.effect_time());
  }
};

#endif  // SRC_TYPE_STR_EDGES_HPP_
