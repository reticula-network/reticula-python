#ifndef SRC_TYPE_STR_IMPLICIT_EVENT_GRAPHS_HPP_
#define SRC_TYPE_STR_IMPLICIT_EVENT_GRAPHS_HPP_

#include <string>

#include <fmt/format.h>

#include <dag/implicit_event_graph.hpp>

#include "common.hpp"
#include "scalars.hpp"
#include "temporal_adjacency.hpp"
#include "edges.hpp"

template <
  dag::temporal_edge EdgeT,
  dag::temporal_adjacency::temporal_adjacency AdjT>
struct type_str<dag::implicit_event_graph<EdgeT, AdjT>> {
  std::string operator()() {
      return fmt::format("implicit_event_graph[{}, {}]",
              type_str<EdgeT>{}(), type_str<AdjT>{}());
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

#endif  // SRC_TYPE_STR_IMPLICIT_EVENT_GRAPHS_HPP_
