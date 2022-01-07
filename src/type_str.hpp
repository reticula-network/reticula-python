#ifndef SRC_TYPE_STR_HPP_
#define SRC_TYPE_STR_HPP_

#include <string>

#include <fmt/format.h>

template<typename T> struct type_str {
    std::string operator()();
};

// signed integer
template <>
struct type_str<int8_t>  { std::string operator()() { return "int8"; } };

template <>
struct type_str<int16_t> { std::string operator()() { return "int16"; } };

template <>
struct type_str<int32_t> { std::string operator()() { return "int32"; } };

template <>
struct type_str<int64_t> { std::string operator()() { return "int64"; } };

template <>
struct type_str<uint8_t>  { std::string operator()() { return "uint8"; } };

template <>
struct type_str<uint16_t> { std::string operator()() { return "uint16"; } };

template <>
struct type_str<uint32_t> { std::string operator()() { return "uint32"; } };

template <>
struct type_str<uint64_t> { std::string operator()() { return "uint64"; } };


// floating point
template <>
struct type_str<float> { std::string operator()()       { return "float"; } };

template <>
struct type_str<double> { std::string operator()()      { return "double"; } };

template <>
struct type_str<long double> { std::string operator()() { return "ldouble"; } };

// signed integer
template <>
struct type_str<std::string> { std::string operator()() { return "string"; } };

// static edge
template <typename VertT>
struct type_str<dag::undirected_edge<VertT>> {
    std::string operator()() {
        return fmt::format("UndirectedEdge_{}", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_edge<VertT>> {
    std::string operator()() {
        return fmt::format("DirectedEdge_{}", type_str<VertT>{}());
    }
};

// temporal edge
template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("UndirectedTemporalEdge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("DirectedTemporalEdge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("DirectedDelayedTemporalEdge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

// static network
template <typename VertT>
struct type_str<dag::undirected_network<VertT>> {
    std::string operator()() {
        return fmt::format("UndirectedNetwork_{}", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_network<VertT>> {
    std::string operator()() {
        return fmt::format("DirectedNetwork_{}", type_str<VertT>{}());
    }
};

// temporal network
template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("UndirectedTemporalNetwork_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("DirectedTemporalNetwork_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("DirectedDelayedTemporalNetwork_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

// Formatters
template <dag::network_edge EdgeT>
struct fmt::formatter<dag::network<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(const dag::network<EdgeT>& a, FormatContext& ctx)
  -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(), "<dag.{} with {} verts and {} edges>",
        type_str<dag::network<EdgeT>>{}(),
        a.vertices().size(), a.edges().size());
  }
};

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

#endif  // SRC_TYPE_STR_HPP_
