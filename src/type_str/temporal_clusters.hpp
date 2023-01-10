#ifndef SRC_TYPE_STR_TEMPORAL_CLUSTERS_HPP_
#define SRC_TYPE_STR_TEMPORAL_CLUSTERS_HPP_

#include <string>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <reticula/temporal_clusters.hpp>

#include "common.hpp"
#include "edges.hpp"
#include "temporal_adjacency.hpp"

template <
  reticula::temporal_network_edge EdgeT,
  reticula::temporal_adjacency::temporal_adjacency AdjT>
struct type_str<reticula::temporal_cluster<EdgeT, AdjT>> {
  std::string operator()() {
      return fmt::format("temporal_cluster[{}, {}]",
              type_str<EdgeT>{}(),
              type_str<AdjT>{}());
  }
};

template <
  reticula::temporal_network_edge EdgeT,
  reticula::temporal_adjacency::temporal_adjacency AdjT>
struct type_str<reticula::temporal_cluster_size<EdgeT, AdjT>> {
  std::string operator()() {
      return fmt::format("temporal_cluster_size[{}, {}]",
              type_str<EdgeT>{}(),
              type_str<AdjT>{}());
  }
};

template <
  reticula::temporal_network_edge EdgeT,
  reticula::temporal_adjacency::temporal_adjacency AdjT>
struct type_str<reticula::temporal_cluster_size_estimate<EdgeT, AdjT>> {
  std::string operator()() {
      return fmt::format("temporal_cluster_size_estimate[{}, {}]",
              type_str<EdgeT>{}(),
              type_str<AdjT>{}());
  }
};

// Formatters

template <
  reticula::temporal_network_edge EdgeT,
  reticula::temporal_adjacency::temporal_adjacency AdjT>
struct fmt::is_range<reticula::temporal_cluster<EdgeT, AdjT>, char> :
    std::false_type {};

template <
  reticula::temporal_network_edge EdgeT,
  reticula::temporal_adjacency::temporal_adjacency AdjT>
struct fmt::formatter<reticula::temporal_cluster<EdgeT, AdjT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::temporal_cluster<EdgeT, AdjT>& a,
      FormatContext& ctx) const -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<{} with volume {} and lifetime ({} {}]>",
        type_str<reticula::temporal_cluster<EdgeT, AdjT>>{}(),
        a.volume(),
        a.lifetime().first,
        a.lifetime().second);
  }
};

template <
  reticula::temporal_network_edge EdgeT,
  reticula::temporal_adjacency::temporal_adjacency AdjT>
struct fmt::formatter<reticula::temporal_cluster_size<EdgeT, AdjT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::temporal_cluster_size<EdgeT, AdjT>& a,
      FormatContext& ctx) const -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<{} with mass {} volume {} and lifetime ({} {}]>",
        type_str<reticula::temporal_cluster_size<EdgeT, AdjT>>{}(),
        a.mass(),
        a.volume(),
        a.lifetime().first,
        a.lifetime().second);
  }
};

template <
  reticula::temporal_network_edge EdgeT,
  reticula::temporal_adjacency::temporal_adjacency AdjT>
struct fmt::formatter<reticula::temporal_cluster_size_estimate<EdgeT, AdjT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::temporal_cluster_size_estimate<EdgeT, AdjT>& a,
      FormatContext& ctx) const -> decltype(ctx.out()) {
    return fmt::format_to(
        ctx.out(),
        "<{} with mass {}±1.1\% volume {}±1.1\% and lifetime ({} {}]>",
        type_str<reticula::temporal_cluster_size_estimate<EdgeT, AdjT>>{}(),
        a.mass_estimate(),
        a.volume_estimate(),
        a.lifetime().first,
        a.lifetime().second);
  }
};

#endif  // SRC_TYPE_STR_TEMPORAL_CLUSTERS_HPP_
