#ifndef SRC_TYPE_STR_INTERVALS_HPP_
#define SRC_TYPE_STR_INTERVALS_HPP_

#include <string>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <reticula/intervals.hpp>

#include "common.hpp"
#include "scalars.hpp"

template <typename TimeT>
struct type_str<reticula::interval_set<TimeT>> {
  std::string operator()() {
      return fmt::format("interval_set[{}]",
              type_str<TimeT>{}());
  }
};


template <typename TimeT>
struct fmt::is_range<reticula::interval_set<TimeT>, char> : std::false_type {};

template <typename TimeT>
struct fmt::formatter<reticula::interval_set<TimeT>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }

  template <typename FormatContext>
  auto format(
      const reticula::interval_set<TimeT>& a,
      FormatContext& ctx) -> decltype(ctx.out()) {
    if (a.begin() != a.end())
      return fmt::format_to(
          ctx.out(),
          "<{} from t={} to t={}>",
          type_str<reticula::interval_set<TimeT>>{}(),
          a.begin()->first, (a.end()-1)->second);
    else
      return fmt::format_to(
          ctx.out(),
          "<{} (empty)>",
          type_str<reticula::interval_set<TimeT>>{}());
  }
};


#endif  // SRC_TYPE_STR_INTERVALS_HPP_

