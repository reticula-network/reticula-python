#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/stl_bind.h>

#include <dag/temporal_clusters.hpp>

#include "type_str/temporal_clusters.hpp"
#include "type_utils.hpp"

namespace nb = nanobind;
using namespace nanobind::literals;

template <dag::temporal_adjacency::temporal_adjacency AdjT>
struct declare_temporal_cluster_containers {
  void operator()(nb::module_ &m) {
    using EdgeT = AdjT::EdgeType;
    using Cluster = dag::temporal_cluster<EdgeT, AdjT>;

    nb::bind_vector<
        std::vector<std::pair<EdgeT, Cluster>>>(m,
                fmt::format("vector_pair_{}_{}",
                    python_type_str<EdgeT>(),
                    python_type_str<Cluster>()).c_str());

    using ClusterSize = dag::temporal_cluster_size<EdgeT, AdjT>;
    nb::bind_vector<
        std::vector<std::pair<EdgeT, ClusterSize>>>(m,
                fmt::format("vector_pair_{}_{}",
                    python_type_str<EdgeT>(),
                    python_type_str<ClusterSize>()).c_str());

    using ClusterSizeEstimate =
      dag::temporal_cluster_size_estimate<EdgeT, AdjT>;
    nb::bind_vector<
        std::vector<std::pair<EdgeT, ClusterSizeEstimate>>>(m,
                fmt::format("vector_pair_{}_{}",
                    python_type_str<EdgeT>(),
                    python_type_str<ClusterSizeEstimate>()).c_str());
  }
};

void declare_typed_temporal_cluster_containers(nb::module_& m) {
  types::run_each<
    metal::transform<
      metal::lambda<declare_temporal_cluster_containers>,
      types::first_order_temporal_adjacency_types>>{}(m);
}
