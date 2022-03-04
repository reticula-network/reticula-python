#ifndef SRC_TYPE_STR_NETWORKS_HPP_
#define SRC_TYPE_STR_NETWORKS_HPP_

#include <string>
#include <fmt/format.h>

#include <dag/networks.hpp>

#include "common.hpp"
#include "scalars.hpp"
#include "edges.hpp"

// static network
template <typename VertT>
struct type_str<dag::undirected_network<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_network[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_network<VertT>> {
    std::string operator()() {
        return fmt::format("directed_network[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::undirected_hypernetwork<VertT>> {
    std::string operator()() {
        return fmt::format("undirected_hypernetwork[{}]", type_str<VertT>{}());
    }
};

template <typename VertT>
struct type_str<dag::directed_hypernetwork<VertT>> {
    std::string operator()() {
        return fmt::format("directed_hypernetwork[{}]", type_str<VertT>{}());
    }
};

// temporal network
template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_network[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_network[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_network<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_network[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::undirected_temporal_hypernetwork<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("undirected_temporal_hypernetwork[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_temporal_hypernetwork<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_temporal_hypernetwork[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

template <typename VertT, typename TimeT>
struct type_str<dag::directed_delayed_temporal_hypernetwork<VertT, TimeT>> {
    std::string operator()() {
        return fmt::format("directed_delayed_temporal_hypernetwork[{}, {}]",
            type_str<VertT>{}(), type_str<TimeT>{}());
    }
};

// formatter

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

#endif  // SRC_TYPE_STR_NETWORKS_HPP_
