#ifndef SRC_TYPE_STR_HPP_
#define SRC_TYPE_STR_HPP_

#include <string>

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <dag/dag.hpp>

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

// non-integer types
template <>
struct type_str<std::string> { std::string operator()() { return "string"; } };

template <typename T1, typename T2>
struct type_str<std::pair<T1, T2>> {
  std::string operator()() {
    return fmt::format("pair_{}_{}", type_str<T1>{}(), type_str<T2>{}());
  }
};

// static edge
template <typename VertT>
struct type_str<dag::undirected_edge<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_edge_{}", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_edge<VertT>> {
    std::string operator()() {
        return fmt::format("directed_edge_{}", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::undirected_hyperedge<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_hyperedge_{}", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_hyperedge<VertT>> {
    std::string operator()() {
        return fmt::format("directed_hyperedge_{}", type_str<VertT>{}());
    }
};

// temporal edge
template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_edge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_edge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_edge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_edge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_hyperedge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_hyperedge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_hyperedge<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_hyperedge_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

// static network
template <typename VertT>
struct type_str<dag::undirected_network<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_network_{}", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_network<VertT>> {
    std::string operator()() {
        return fmt::format("directed_network_{}", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::undirected_hypernetwork<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_hypernetwork_{}", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_hypernetwork<VertT>> {
    std::string operator()() {
        return fmt::format("directed_hypernetwork_{}", type_str<VertT>{}());
    }
};

// temporal network
template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_network_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_network_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_network_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_hypernetwork<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_hypernetwork_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_hypernetwork<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_hypernetwork_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_hypernetwork<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_hypernetwork_{}_{}",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

// components
template <dag::network_vertex VertT>
struct type_str<dag::component<VertT>> {
    std::string operator()() {
        return fmt::format("component_{}",
            type_str<VertT>{}());
    }
};

template <dag::network_vertex VertT>
struct type_str<dag::component_size<VertT>> {
    std::string operator()() {
        return fmt::format("component_size_{}",
            type_str<VertT>{}());
    }
};

template <dag::network_vertex VertT>
struct type_str<dag::component_size_estimate<VertT>> {
    std::string operator()() {
        return fmt::format("component_size_estimate_{}",
            type_str<VertT>{}());
    }
};

// random_state
template <>
struct type_str<std::mt19937_64> {
  std::string operator()() { return "mersenne_twister"; }
};

// temporal adjacency
template <dag::temporal_edge EdgeT>
struct type_str<dag::temporal_adjacency::simple<EdgeT>> {
  std::string operator()() {
      return fmt::format("simple_{}",
              type_str<EdgeT>{}());
  }
};

template <dag::temporal_edge EdgeT>
struct type_str<dag::temporal_adjacency::limited_waiting_time<EdgeT>> {
  std::string operator()() {
      return fmt::format("limited_waiting_time_{}",
              type_str<EdgeT>{}());
  }
};

template <dag::temporal_edge EdgeT>
struct type_str<dag::temporal_adjacency::exponential<EdgeT>> {
  std::string operator()() {
      return fmt::format("exponential_{}",
              type_str<EdgeT>{}());
  }
};

template <dag::temporal_edge EdgeT>
struct type_str<dag::temporal_adjacency::geometric<EdgeT>> {
  std::string operator()() {
      return fmt::format("geometric_{}",
              type_str<EdgeT>{}());
  }
};

// implicit event graph
template <
  dag::temporal_edge EdgeT,
  dag::temporal_adjacency::temporal_adjacency AdjT>
struct type_str<dag::implicit_event_graph<EdgeT, AdjT>> {
  std::string operator()() {
      return fmt::format("implicit_event_graph_{}_{}",
              type_str<EdgeT>{}(), type_str<AdjT>{}());
  }
};

// interval sets
template <typename TimeT>
struct type_str<dag::interval_set<TimeT>> {
  std::string operator()() {
      return fmt::format("interval_set_{}",
              type_str<TimeT>{}());
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

// components

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

// temporal_adjacency

template <dag::temporal_edge EdgeT>
struct fmt::formatter<dag::temporal_adjacency::simple<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::temporal_adjacency::simple<EdgeT>& /* a */,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.temporal_adjacency.{}>",
        type_str<dag::temporal_adjacency::simple<EdgeT>>{}());
  }
};


template <dag::temporal_edge EdgeT>
struct fmt::formatter<dag::temporal_adjacency::limited_waiting_time<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::temporal_adjacency::limited_waiting_time<EdgeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.temporal_adjacency.{} dt={}>",
        type_str<dag::temporal_adjacency::limited_waiting_time<EdgeT>>{}(), a.dt());
  }
};

template <dag::temporal_edge EdgeT>
struct fmt::formatter<dag::temporal_adjacency::exponential<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::temporal_adjacency::exponential<EdgeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.temporal_adjacency.{} rate={}>",
        type_str<dag::temporal_adjacency::exponential<EdgeT>>{}(), a.rate());
  }
};


template <dag::temporal_edge EdgeT>
struct fmt::formatter<dag::temporal_adjacency::geometric<EdgeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::temporal_adjacency::geometric<EdgeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.temporal_adjacency.{} rate={}>",
        type_str<dag::temporal_adjacency::geometric<EdgeT>>{}(), a.p());
  }
};

template <
  dag::temporal_edge EdgeT,
  dag::temporal_adjacency::temporal_adjacency AdjT>
struct fmt::formatter<dag::implicit_event_graph<EdgeT, AdjT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::implicit_event_graph<EdgeT, AdjT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{} with {} verts, {} events and temporal adjacency {}>",
        type_str<dag::implicit_event_graph<EdgeT, AdjT>>{}(),
        a.temporal_net_vertices().size(),
        a.events_cause().size(),
        a.temporal_adjacency());
  }
};

template <typename TimeT>
struct fmt::is_range<dag::interval_set<TimeT>, char> : std::false_type {};

template <typename TimeT>
struct fmt::formatter<dag::interval_set<TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const dag::interval_set<TimeT>& /* a */,
      FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<dag.{}>",
        type_str<dag::interval_set<TimeT>>{}());
  }
};
#endif  // SRC_TYPE_STR_HPP_
