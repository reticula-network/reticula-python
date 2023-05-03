cmake_minimum_required(VERSION 3.12)

project(reticula_python LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  reticula
  GIT_REPOSITORY https://github.com/reticula-network/reticula.git
  GIT_TAG 889001ad333287005c3caa43c462e621aa840a56)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 9.1.0)

FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/brunocodutra/metal.git
  GIT_TAG v2.1.4)

# Perform a release build by default
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Create CMake targets for all Python components needed by nanobind
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.26 AND Python_INTERPRETER_ID STREQUAL "Python")
  find_package(Python 3.8 COMPONENTS Interpreter Development.Module Development.SABIModule REQUIRED)
else()
  find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
endif()


execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)

list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")

find_package(nanobind CONFIG REQUIRED)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON) # turns off nanobind LTO flags

FetchContent_MakeAvailable(reticula fmt metal)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

nanobind_add_module(_reticula_ext
  NB_STATIC

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
  src/microcanonical_reference_models.cpp
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
  src/algorithms/basic_temporal.cpp
  src/algorithms/density.cpp
  src/algorithms/directed_connectivity.cpp
  src/algorithms/temporal_adjacency.cpp
  src/algorithms/undirected_connectivity.cpp)
target_link_libraries(_reticula_ext
  PRIVATE reticula fmt Metal)
set_target_properties(_reticula_ext
  PROPERTIES CXX_VISIBILITY_PRESET hidden)

install(TARGETS _reticula_ext DESTINATION .)

set(lib_path "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${lib_path}" is_system)
if ("${is_system}" STREQUAL "-1")
  # The following is necessary for installation in a virtual
  # environment `python -m pip venv env`
  set_target_properties(_reticula_ext PROPERTIES
      INSTALL_RPATH_USE_LINK_PATH TRUE
      INSTALL_RPATH "${lib_path}")
endif()

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")
