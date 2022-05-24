cmake_minimum_required(VERSION 3.12)

project(reticula_python LANGUAGES CXX VERSION 0.0.4)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  reticula
  GIT_REPOSITORY https://github.com/reticula-network/reticula.git
  GIT_TAG 8e33c3a)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 8.1.1)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.9.0)

FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/brunocodutra/metal.git
  GIT_TAG v2.1.4)

FetchContent_GetProperties(pybind11)
if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
endif()

FetchContent_MakeAvailable(reticula fmt metal)


pybind11_add_module(reticula_ext src/main.cpp)
set_target_properties(reticula_ext
  PROPERTIES CXX_VISIBILITY_PRESET hidden)

function(reticula_library name)
  add_library(${PROJECT_NAME}_${name} ${ARGN})
  set_target_properties(${PROJECT_NAME}_${name}
    PROPERTIES CXX_VISIBILITY_PRESET hidden)
  target_link_libraries(${PROJECT_NAME}_${name} PRIVATE
    reticula fmt Metal pybind11::pybind11)
  target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_${name})
endfunction()

reticula_library(scaler_types src/scalar_types.cpp)
reticula_library(random_state src/random_state.cpp)
reticula_library(distributions src/distributions.cpp)
reticula_library(interval_sets src/interval_sets.cpp)
reticula_library(temporal_edges src/temporal_edges.cpp)
reticula_library(temporal_hyperedges src/temporal_hyperedges.cpp)
reticula_library(static_edges src/static_edges.cpp)
reticula_library(static_hyperedges src/static_hyperedges.cpp)
reticula_library(networks src/networks.cpp)
reticula_library(temporal_adjacency src/temporal_adjacency.cpp)
reticula_library(implicit_event_graphs src/implicit_event_graphs.cpp)
reticula_library(implicit_event_graph_components
  src/implicit_event_graph_components.cpp)
reticula_library(generators src/generators.cpp)
reticula_library(random_networks src/random_networks.cpp)
reticula_library(random_activation_networks src/random_activation_networks.cpp)
reticula_library(temporal_clusters src/temporal_clusters.cpp)
reticula_library(temporal_cluster_containers
  src/temporal_cluster_containers.cpp)
reticula_library(components src/components.cpp)
reticula_library(component_containers src/component_containers.cpp)
reticula_library(io src/io.cpp)
reticula_library(algorithms
  src/algorithms.cpp
  src/algorithms/directed.cpp
  src/algorithms/undirected.cpp
  src/algorithms/temporal.cpp)
reticula_library(microcanonical_reference_models
  src/microcanonical_reference_models.cpp)
reticula_library(type_lists src/type_lists.cpp)

install(TARGETS reticula_ext DESTINATION .)

set(lib_path "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${lib_path}" is_system)
if ("${is_system}" STREQUAL "-1")
    # The following is necessary for installation in a virtual
    # environment `python -m pip venv env`
    set_target_properties(reticula_ext PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH TRUE
        INSTALL_RPATH "${lib_path}")
endif()
