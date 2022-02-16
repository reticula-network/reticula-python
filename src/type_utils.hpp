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
  /* using time_types = metal::list< */
  /*   uint16_t, uint32_t, uint64_t, */
  /*   int16_t, int32_t, int64_t, */
  /*   float, double, long double>; */

  using time_types = metal::list<double>;

  /* using integer_vert_types = metal::list< */
  /*   uint16_t, uint32_t, uint64_t, */
  /*   int16_t, int32_t, int64_t>; */

  using integer_vert_types = metal::list<int64_t>;

  using random_state_types = metal::list<std::mt19937_64>;
#else  // debug release
  using time_types = metal::list<double>;

  using integer_vert_types = metal::list<int64_t>;

  using random_state_types = metal::list<std::mt19937_64>;
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

  using first_order_vert_types =
      metal::join<simple_vert_types, compount_vert_type>;

  // first-order static edges
  using first_order_undirected_edges =
    metal::transform<
      metal::lambda<dag::undirected_edge>,
      first_order_vert_types>;

  using first_order_directed_edges =
    metal::transform<
      metal::lambda<dag::directed_edge>,
      first_order_vert_types>;

  using first_order_undirected_hyperedges =
    metal::transform<
      metal::lambda<dag::undirected_hyperedge>,
      first_order_vert_types>;

  using first_order_directed_hyperedges =
    metal::transform<
      metal::lambda<dag::directed_hyperedge>,
      first_order_vert_types>;

  using first_order_static_edges = metal::join<
    first_order_undirected_edges,
    first_order_undirected_hyperedges,
    first_order_directed_edges,
    first_order_directed_hyperedges>;

  // first-order temporal edges
  using first_order_temporal_type_parameter_combinations =
    metal::cartesian<first_order_vert_types, time_types>;

  using first_order_undirected_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::undirected_temporal_edge>>,
      first_order_temporal_type_parameter_combinations>;

  using first_order_directed_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::directed_temporal_edge>>,
      first_order_temporal_type_parameter_combinations>;

  using first_order_directed_delayed_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::directed_delayed_temporal_edge>>,
      first_order_temporal_type_parameter_combinations>;

  // simple (first order) temporal hyperedges
  using first_order_undirected_temporal_hyperedges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::undirected_temporal_hyperedge>>,
      first_order_temporal_type_parameter_combinations>;

  using first_order_directed_temporal_hyperedges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::directed_temporal_hyperedge>>,
      first_order_temporal_type_parameter_combinations>;

  using first_order_directed_delayed_temporal_hyperedges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::directed_delayed_temporal_hyperedge>>,
      first_order_temporal_type_parameter_combinations>;

  // all together now
  using first_order_temporal_edges = metal::join<
    first_order_undirected_temporal_edges,
    first_order_directed_temporal_edges,
    first_order_directed_delayed_temporal_edges,
    first_order_undirected_temporal_hyperedges,
    first_order_directed_temporal_hyperedges,
    first_order_directed_delayed_temporal_hyperedges>;

  // second order static edges
  // For now, let's only define static (non-hyper) edges of temporal edges (ala
  // event graph)

  using second_order_directed_edges =
    metal::transform<
      metal::lambda<dag::directed_edge>,
      first_order_temporal_edges>;

  using second_order_undirected_edges =
    metal::transform<
      metal::lambda<dag::undirected_edge>,
      first_order_temporal_edges>;

  using second_order_static_edges = metal::join<
    second_order_undirected_edges,
    second_order_directed_edges>;

  // all vert_types
  using all_vert_types = metal::join<
    first_order_vert_types,
    first_order_temporal_edges>;

  // all edge_types
  using all_edge_types = metal::join<
    first_order_static_edges,
    first_order_temporal_edges,
    second_order_static_edges>;


  template <dag::temporal_edge T>
  using is_integral_time = std::is_integral<typename T::TimeType>;

  template <dag::temporal_edge T>
  using is_floating_point_time = std::is_floating_point<typename T::TimeType>;

  // temporal adjacency types
  using first_order_temporal_adjacency_types = metal::join<
    metal::transform<
      metal::lambda<dag::temporal_adjacency::simple>,
      first_order_temporal_edges>,
    metal::transform<
      metal::lambda<dag::temporal_adjacency::limited_waiting_time>,
      first_order_temporal_edges>,
    metal::transform<
      metal::lambda<dag::temporal_adjacency::geometric>,
      metal::copy_if<
        first_order_temporal_edges,
        metal::trait<is_integral_time>>>,
    metal::transform<
      metal::lambda<dag::temporal_adjacency::exponential>,
      metal::copy_if<
        first_order_temporal_edges,
        metal::trait<is_floating_point_time>>>
    >;
}  // namespace types
#endif  // SRC_TYPE_UTILS_HPP_
