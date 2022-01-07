#ifndef SRC_TYPE_UTILS_HPP_
#define SRC_TYPE_UTILS_HPP_

#include <utility>

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

  using integer_vert_types = metal::list<
    int16_t, int32_t, int64_t>;
  using noninteger_vert_types = metal::list<std::string>;

  using simple_vert_types = metal::join<
    integer_vert_types, noninteger_vert_types>;

  // using simple_static_hyperedges = join<
  //   simple_vert_types::wrap<dag::undirected_hyperedge>,
  //   simple_vert_types::wrap<dag::directed_hyperedge>
  //     >::type;

  using time_types = metal::list<
    int16_t, int32_t, int64_t,
    float, double, long double>;


  // simple (first order) temporal edges

  using simple_undirected_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::undirected_temporal_edge>>,
      metal::cartesian<types::simple_vert_types, types::time_types>>;

  using simple_directed_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::directed_temporal_edge>>,
      metal::cartesian<types::simple_vert_types, types::time_types>>;

  using simple_directed_delayed_temporal_edges =
    metal::transform<
      metal::partial<
        metal::lambda<metal::apply>,
        metal::lambda<dag::directed_delayed_temporal_edge>>,
      metal::cartesian<types::simple_vert_types, types::time_types>>;

  using simple_temporal_edges = metal::join<
    simple_undirected_temporal_edges,
    simple_directed_temporal_edges,
    simple_directed_delayed_temporal_edges>;

  // simple (first order) temporal hyperedges

  /* using simple_undirected_temporal_hyperedges = */
  /*   metal::transform< */
  /*     metal::partial< */
  /*       metal::lambda<metal::apply>, */
  /*       metal::lambda<dag::undirected_temporal_hyperedge>>, */
  /*     metal::cartesian<types::simple_vert_types, types::time_types>>; */

  /* using simple_directed_temporal_edges = */
  /*   metal::transform< */
  /*     metal::partial< */
  /*       metal::lambda<metal::apply>, */
  /*       metal::lambda<dag::directed_temporal_hyperedge>>, */
  /*     metal::cartesian<types::simple_vert_types, types::time_types>>; */

  /* using simple_directed_delayed_temporal_hyperedges = */
  /*   metal::transform< */
  /*     metal::partial< */
  /*       metal::lambda<metal::apply>, */
  /*       metal::lambda<dag::directed_delayed_temporal_hyperedge>>, */
  /*     metal::cartesian<types::simple_vert_types, types::time_types>>; */

  /* using simple_temporal_hyperedges = metal::join< */
  /*   simple_undirected_temporal_hyperedges, */
  /*   simple_directed_temporal_hyperedges, */
  /*   simple_directed_delayed_temporal_hyperedges>; */
}  // namespace types
#endif  // SRC_TYPE_UTILS_HPP_
