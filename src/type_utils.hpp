#ifndef SRC_TYPE_UTILS_HPP_
#define SRC_TYPE_UTILS_HPP_

#include <utility>
#include <random>

#include <metal.hpp>
#include <dag/dag.hpp>

namespace types {
  template <typename List>
  struct run_each;

  template <typename... Ts>
  struct run_each<metal::list<Ts...>> {
    template <typename... Args>
    void operator()(Args&&... args) {
      (Ts{}(std::forward<Args>(args)...), ...);
    }
  };

#ifdef NDEBUG
  using time_types = metal::list<
    uint16_t, uint32_t, uint64_t,
    int16_t, int32_t, int64_t,
    float, double, long double>;

  using integer_vert_types = metal::list<
    uint16_t, uint32_t, uint64_t,
    int16_t, int32_t, int64_t>;

  using random_state_types = metal::list<
    std::mt19937_64>;
#else  // debug release
  using time_types = metal::list<
    int64_t, long double>;

  using integer_vert_types = metal::list<
    int64_t>;

  using random_state_types = metal::list<
    std::mt19937_64>;
#endif

  using noninteger_vert_types = metal::list<std::string>;

  using simple_vert_types = metal::join<
    integer_vert_types, noninteger_vert_types>;

  using pair_vert_types =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<std::pair>>,
      metal::cartesian<simple_vert_types, simple_vert_types>>;

  using compount_vert_type = metal::join<pair_vert_types>;

  using first_order_vert_types = metal::join<
    simple_vert_types, compount_vert_type>;

  // using simple_static_hyperedges = join<
  //   first_order_vert_wrap<dag::undirected_hyperedge>,
  //   first_order_vert_wrap<dag::directed_hyperedge>
  //     >::type;

  // simple (first order) temporal edges

  using first_order_undirected_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::undirected_temporal_edge>>,
      metal::cartesian<first_order_vert_types, time_types>>;

  using first_order_directed_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::directed_temporal_edge>>,
      metal::cartesian<first_order_vert_types, time_types>>;

  using first_order_directed_delayed_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::directed_delayed_temporal_edge>>,
      metal::cartesian<first_order_vert_types, time_types>>;

  using first_order_temporal_edges = metal::join<
    first_order_undirected_temporal_edges,
    first_order_directed_temporal_edges,
    first_order_directed_delayed_temporal_edges>;

  // simple (first order) temporal hyperedges

  /* using simple_undirected_temporal_hyperedges = */
  /*   metal::transform< */
  /*     metal::partial< */
  /*       metal::lambda<metal::apply>, */
  /*       metal::lambda<dag::undirected_temporal_hyperedge>>, */
  /*     metal::cartesian<first_order_vert_types, time_types>>; */

  /* using simple_directed_temporal_edges = */
  /*   metal::transform< */
  /*     metal::partial< */
  /*       metal::lambda<metal::apply>, */
  /*       metal::lambda<dag::directed_temporal_hyperedge>>, */
  /*     metal::cartesian<first_order_vert_types, time_types>>; */

  /* using simple_directed_delayed_temporal_hyperedges = */
  /*   metal::transform< */
  /*     metal::partial< */
  /*       metal::lambda<metal::apply>, */
  /*       metal::lambda<dag::directed_delayed_temporal_hyperedge>>, */
  /*     metal::cartesian<first_order_vert_types, time_types>>; */

  /* using simple_temporal_hyperedges = metal::join< */
  /*   simple_undirected_temporal_hyperedges, */
  /*   simple_directed_temporal_hyperedges, */
  /*   simple_directed_delayed_temporal_hyperedges>; */
}  // namespace types
#endif  // SRC_TYPE_UTILS_HPP_
