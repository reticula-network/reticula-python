cmake_minimum_required(VERSION 3.12)

project(reticula_python LANGUAGES CXX VERSION 0.7.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  reticula
  GIT_REPOSITORY https://github.com/reticula-network/reticula.git
  GIT_TAG f8a5be4)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 9.1.0)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.10.3)

FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/brunocodutra/metal.git
  GIT_TAG v2.1.4)

FetchContent_GetProperties(pybind11)
if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON) # turns off pybind11 LTO flags

FetchContent_MakeAvailable(reticula fmt metal)

pybind11_add_module(reticula_ext src/main.cpp
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
  src/generators.cpp
  src/random_networks.cpp
  src/random_activation_networks.cpp
  src/temporal_clusters.cpp
  src/components.cpp
  src/io.cpp
  src/algorithms.cpp
  src/algorithms/assortativity.cpp
  src/algorithms/degree.cpp
  src/algorithms/add_operations.cpp
  src/algorithms/remove_operations.cpp
  src/algorithms/basic_temporal.cpp
  src/algorithms/density.cpp
  src/algorithms/directed_connectivity.cpp
  src/algorithms/edge_occupation.cpp
  src/algorithms/vertex_occupation.cpp
  src/algorithms/subgraph.cpp
  src/algorithms/temporal_adjacency.cpp
  src/algorithms/undirected_connectivity.cpp
  src/microcanonical_reference_models.cpp
  src/type_lists.cpp)
target_link_libraries(reticula_ext PRIVATE reticula fmt Metal)
set_target_properties(reticula_ext
  PROPERTIES CXX_VISIBILITY_PRESET hidden)

install(TARGETS reticula_ext DESTINATION .)

set(lib_path "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${lib_path}" is_system)
if ("${is_system}" STREQUAL "-1")
    # The following is necessary for installation in a virtual
    # environment `python -m pip venv env`
    set_target_properties(reticula_ext PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH TRUE
        INSTALL_RPATH "${lib_path}")

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

endif()
