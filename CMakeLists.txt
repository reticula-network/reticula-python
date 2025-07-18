cmake_minimum_required(VERSION 3.28)

project(reticula_python LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  reticula
  GIT_REPOSITORY https://github.com/reticula-network/reticula.git
  GIT_TAG 15b3ad5057c0e89ef6fb619677496f8d1a7e0992)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 9.1.0)

FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/brunocodutra/metal.git
  GIT_TAG v2.1.4
  EXCLUDE_FROM_ALL)

find_package(Python 3.10
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule)

find_package(nanobind CONFIG REQUIRED)

if (NOT MSVC)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

FetchContent_MakeAvailable(reticula fmt metal)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

nanobind_add_module(_reticula_ext
  NB_DOMAIN reticula
  STABLE_ABI
  NB_STATIC
  NOMINSIZE

  src/main.cpp

  src/types.cpp
  src/scalar_types.cpp
  src/random_state.cpp
  src/distributions.cpp
  src/interval_sets.cpp
  src/temporal_edges.cpp
  src/temporal_hyperedges.cpp
  src/static_edges.cpp
  src/static_hyperedges.cpp
  src/networks.cpp
  src/temporal_adjacency.cpp
  src/implicit_event_graphs.cpp
  src/implicit_event_graph_components.cpp
  src/components.cpp
  src/temporal_clusters.cpp
  src/type_lists.cpp

  src/generators.cpp
  src/static_microcanonical_reference_models.cpp
  src/temporal_microcanonical_reference_models.cpp
  src/simple_generators.cpp
  src/random_networks.cpp
  src/random_activation_networks.cpp

  src/io.cpp

  src/operations.cpp
  src/operations/subgraph.cpp
  src/operations/add_operations.cpp
  src/operations/remove_operations.cpp
  src/operations/edge_occupation.cpp
  src/operations/vertex_occupation.cpp

  src/algorithms.cpp
  src/algorithms/assortativity.cpp
  src/algorithms/degree.cpp
  src/algorithms/edge_degree.cpp
  src/algorithms/basic_temporal.cpp
  src/algorithms/density.cpp
  src/algorithms/directed_connectivity.cpp
  src/algorithms/temporal_adjacency.cpp
  src/algorithms/undirected_connectivity.cpp)
target_link_libraries(_reticula_ext
  PRIVATE reticula fmt Metal)
set_target_properties(_reticula_ext
  PROPERTIES CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON)

install(TARGETS _reticula_ext DESTINATION reticula)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")
