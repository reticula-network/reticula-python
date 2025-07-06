#ifndef SRC_TYPE_UTILS_HPP_
#define SRC_TYPE_UTILS_HPP_

#include <utility>
#include <random>

#include <metal.hpp>

#include <reticula/networks.hpp>
#include <reticula/static_edges.hpp>
#include <reticula/temporal_edges.hpp>
#include <reticula/static_hyperedges.hpp>
#include <reticula/temporal_hyperedges.hpp>
#include <reticula/temporal_adjacency.hpp>

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

  template<class seq>
  using unique = metal::accumulate<
    metal::bind<
      metal::lambda<metal::if_>,
      metal::lambda<metal::contains>, metal::_1,
      metal::lambda<metal::append>>, metal::list<>, seq>;

  /* using time_types = metal::list< */
  /*   uint16_t, uint32_t, uint64_t, */
  /*   int16_t, int32_t, int64_t, */
  /*   float, double, long double>; */

  using time_types = metal::list<double, int64_t>;

  /* using integer_vert_types = metal::list< */
  /*   uint16_t, uint32_t, uint64_t, */
  /*   int16_t, int32_t, int64_t>; */

  using integer_vert_types = metal::list<int64_t>;

  using random_state_types = metal::list<std::mt19937_64>;

  using noninteger_vert_types = metal::list<std::string>;

  using simple_vert_types = metal::join<
    integer_vert_types, noninteger_vert_types>;

  using pair_vert_types =
    metal::transform<
      metal::bind<
        metal::lambda<std::pair>,
	metal::_1, metal::_1>,
      simple_vert_types>;

  using compound_vert_type = metal::join<pair_vert_types>;

  using first_order_vert_types =
      metal::join<simple_vert_types, compound_vert_type>;

  // first-order static edges
  using first_order_undirected_edges =
    metal::transform<
      metal::lambda<reticula::undirected_edge>,
      first_order_vert_types>;

  using first_order_directed_edges =
    metal::transform<
      metal::lambda<reticula::directed_edge>,
      first_order_vert_types>;

  using first_order_undirected_hyperedges =
    metal::transform<
      metal::lambda<reticula::undirected_hyperedge>,
      first_order_vert_types>;

  using first_order_directed_hyperedges =
    metal::transform<
      metal::lambda<reticula::directed_hyperedge>,
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
        metal::lambda<reticula::undirected_temporal_edge>>,
      first_order_temporal_type_parameter_combinations>;

  using first_order_directed_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<reticula::directed_temporal_edge>>,
      first_order_temporal_type_parameter_combinations>;

  using first_order_directed_delayed_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<reticula::directed_delayed_temporal_edge>>,
      first_order_temporal_type_parameter_combinations>;

  // simple (first order) temporal hyperedges
  using first_order_undirected_temporal_hyperedges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<reticula::undirected_temporal_hyperedge>>,
      first_order_temporal_type_parameter_combinations>;

  using first_order_directed_temporal_hyperedges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<reticula::directed_temporal_hyperedge>>,
      first_order_temporal_type_parameter_combinations>;

  using first_order_directed_delayed_temporal_hyperedges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<reticula::directed_delayed_temporal_hyperedge>>,
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
      metal::lambda<reticula::directed_edge>,
      first_order_temporal_edges>;

  using second_order_undirected_edges =
    metal::transform<
      metal::lambda<reticula::undirected_edge>,
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


  template <reticula::temporal_network_edge T>
  using is_integral_time = std::is_integral<typename T::TimeType>;

  template <reticula::temporal_network_edge T>
  using is_floating_point_time = std::is_floating_point<typename T::TimeType>;

  // temporal adjacency types
  using first_order_temporal_adjacency_types = metal::join<
    metal::transform<
      metal::lambda<reticula::temporal_adjacency::simple>,
      first_order_temporal_edges>,
    metal::transform<
      metal::lambda<reticula::temporal_adjacency::limited_waiting_time>,
      first_order_temporal_edges>,
    metal::transform<
      metal::lambda<reticula::temporal_adjacency::geometric>,
      metal::copy_if<
        first_order_temporal_edges,
        metal::trait<is_integral_time>>>,
    metal::transform<
      metal::lambda<reticula::temporal_adjacency::exponential>,
      metal::copy_if<
        first_order_temporal_edges,
        metal::trait<is_floating_point_time>>>
    >;
}  // namespace types
#endif  // SRC_TYPE_UTILS_HPP_
