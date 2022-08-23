#ifndef SRC_TYPE_STR_EDGES_HPP_
#define SRC_TYPE_STR_EDGES_HPP_

#include <string>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <reticula/static_edges.hpp>
#include <reticula/static_hyperedges.hpp>
#include <reticula/temporal_edges.hpp>
#include <reticula/temporal_hyperedges.hpp>

#include "common.hpp"
#include "scalars.hpp"

// static edge

template <typename VertT>
struct type_str<reticula::undirected_edge<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_edge[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<reticula::directed_edge<VertT>> {
    std::string operator()() {
        return fmt::format("directed_edge[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<reticula::undirected_hyperedge<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_hyperedge[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<reticula::directed_hyperedge<VertT>> {
    std::string operator()() {
        return fmt::format("directed_hyperedge[{}]", type_str<VertT>{}());
    }
};

// temporal edge
template <typename VertT, typename TimeT>
struct type_str<reticula::undirected_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_edge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<reticula::directed_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_edge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<reticula::directed_delayed_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_edge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<reticula::undirected_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_hyperedge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<reticula::directed_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_hyperedge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_hyperedge[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

// formatters

// static edges

template <reticula::network_vertex VertT>
struct fmt::formatter<reticula::undirected_edge<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const reticula::undirected_edge<VertT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    auto vs = a.incident_verts();
    return fmt::format_to(
        ctx.out(), "{}({}, {})",
        type_str<reticula::undirected_edge<VertT>>{}(),
        vs.front(), vs.back());
  }
};


template <reticula::network_vertex VertT>
struct fmt::formatter<reticula::directed_edge<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const reticula::directed_edge<VertT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "{}({}, {})",
        type_str<reticula::directed_edge<VertT>>{}(),
        a.tail(), a.head());
  }
};

template <reticula::network_vertex VertT>
struct fmt::formatter<reticula::undirected_hyperedge<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const reticula::undirected_hyperedge<VertT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(), "{}({})",
        type_str<reticula::undirected_hyperedge<VertT>>{}(),
        a.incident_verts());
  }
};


template <reticula::network_vertex VertT>
struct fmt::formatter<reticula::directed_hyperedge<VertT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const reticula::directed_hyperedge<VertT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "{}({}, {})",
        type_str<reticula::directed_hyperedge<VertT>>{}(),
        a.tails(), a.heads());
  }
};

// temporal edges
template <reticula::network_vertex VertT, typename TimeT>
struct fmt::formatter<reticula::undirected_temporal_edge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::undirected_temporal_edge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    auto vs = a.incident_verts();
    return fmt::format_to(
        ctx.out(), "{}({}, {}, time={})",
        type_str<reticula::undirected_temporal_edge<VertT, TimeT>>{}(),
        vs.front(), vs.back(), a.effect_time());
  }
};

template <reticula::network_vertex VertT, typename TimeT>
struct fmt::formatter<reticula::directed_temporal_edge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::directed_temporal_edge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "{}({}, {}, time={})",
        type_str<reticula::directed_temporal_edge<VertT, TimeT>>{}(),
        a.tail(), a.head(), a.effect_time());
  }
};

template <reticula::network_vertex VertT, typename TimeT>
struct fmt::formatter<reticula::directed_delayed_temporal_edge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::directed_delayed_temporal_edge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "{}({}, {}, cause_time={}, effect_time={})",
        type_str<reticula::directed_delayed_temporal_edge<VertT, TimeT>>{}(),
        a.tail(), a.head(), a.cause_time(), a.effect_time());
  }
};

template <reticula::network_vertex VertT, typename TimeT>
struct fmt::formatter<reticula::undirected_temporal_hyperedge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::undirected_temporal_hyperedge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(), "{}({}, time={})",
        type_str<reticula::undirected_temporal_hyperedge<VertT, TimeT>>{}(),
        a.incident_verts(), a.effect_time());
  }
};

template <reticula::network_vertex VertT, typename TimeT>
struct fmt::formatter<reticula::directed_temporal_hyperedge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::directed_temporal_hyperedge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "{}({}, {}, time={})",
        type_str<reticula::directed_temporal_hyperedge<VertT, TimeT>>{}(),
        a.tails(), a.heads(), a.effect_time());
  }
};

template <reticula::network_vertex VertT, typename TimeT>
struct fmt::formatter<reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "{}({}, {}, cause_time={}, effect_time={})",
        type_str<reticula::directed_delayed_temporal_hyperedge<VertT, TimeT>>{}(),
        a.tails(), a.heads(), a.cause_time(), a.effect_time());
  }
};

#endif  // SRC_TYPE_STR_EDGES_HPP_
