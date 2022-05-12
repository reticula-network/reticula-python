cmake_minimum_required(VERSION 3.12)

project(reticula_python LANGUAGES CXX VERSION 0.0.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  reticula
  GIT_REPOSITORY https://github.com/reticula-network/reticula.git
  GIT_TAG ab06ac5)

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

add_library(${PROJECT_NAME}_scaler_types src/scalar_types.cpp)
set_target_properties(${PROJECT_NAME}_scaler_types
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_scaler_types PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_scaler_types)

add_library(${PROJECT_NAME}_random_state src/random_state.cpp)
set_target_properties(${PROJECT_NAME}_random_state
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_random_state PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_random_state)

add_library(${PROJECT_NAME}_interval_sets src/interval_sets.cpp)
set_target_properties(${PROJECT_NAME}_interval_sets
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_interval_sets PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_interval_sets)

add_library(${PROJECT_NAME}_temporal_edges src/temporal_edges.cpp)
set_target_properties(${PROJECT_NAME}_temporal_edges
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_temporal_edges PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_temporal_edges)

add_library(${PROJECT_NAME}_temporal_hyperedges src/temporal_hyperedges.cpp)
set_target_properties(${PROJECT_NAME}_temporal_hyperedges
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_temporal_hyperedges PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_temporal_hyperedges)


add_library(${PROJECT_NAME}_static_edges src/static_edges.cpp)
set_target_properties(${PROJECT_NAME}_static_edges
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_static_edges PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_static_edges)

add_library(${PROJECT_NAME}_static_hyperedges src/static_hyperedges.cpp)
set_target_properties(${PROJECT_NAME}_static_hyperedges
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_static_hyperedges PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_static_hyperedges)


add_library(${PROJECT_NAME}_networks src/networks.cpp)
set_target_properties(${PROJECT_NAME}_networks
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_networks PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_networks)


add_library(${PROJECT_NAME}_temporal_adjacency src/temporal_adjacency.cpp)
set_target_properties(${PROJECT_NAME}_temporal_adjacency
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_temporal_adjacency PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_temporal_adjacency)


add_library(${PROJECT_NAME}_implicit_event_graphs src/implicit_event_graphs.cpp)
set_target_properties(${PROJECT_NAME}_implicit_event_graphs
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_implicit_event_graphs PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_implicit_event_graphs)

add_library(${PROJECT_NAME}_implicit_event_graph_components
  src/implicit_event_graph_components.cpp)
set_target_properties(${PROJECT_NAME}_implicit_event_graph_components
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_implicit_event_graph_components PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE
  ${PROJECT_NAME}_implicit_event_graph_components)

add_library(${PROJECT_NAME}_generators src/generators.cpp)
set_target_properties(${PROJECT_NAME}_generators
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_generators PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_generators)


add_library(${PROJECT_NAME}_random_networks src/random_networks.cpp)
set_target_properties(${PROJECT_NAME}_random_networks
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_random_networks PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_random_networks)

add_library(${PROJECT_NAME}_temporal_clusters src/temporal_clusters.cpp)
set_target_properties(${PROJECT_NAME}_temporal_clusters
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_temporal_clusters PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_temporal_clusters)

add_library(${PROJECT_NAME}_temporal_cluster_containers
  src/temporal_cluster_containers.cpp)
set_target_properties(${PROJECT_NAME}_temporal_cluster_containers
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_temporal_cluster_containers PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE
  ${PROJECT_NAME}_temporal_cluster_containers)

add_library(${PROJECT_NAME}_components src/components.cpp)
set_target_properties(${PROJECT_NAME}_components
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_components PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_components)

add_library(${PROJECT_NAME}_component_containers src/component_containers.cpp)
set_target_properties(${PROJECT_NAME}_component_containers
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_component_containers PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_component_containers)

add_library(${PROJECT_NAME}_io src/io.cpp)
set_target_properties(${PROJECT_NAME}_io
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_io PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_io)


add_library(${PROJECT_NAME}_algorithms
  src/algorithms.cpp
  src/algorithms/directed.cpp
  src/algorithms/undirected.cpp
  src/algorithms/temporal.cpp)
set_target_properties(${PROJECT_NAME}_algorithms
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_algorithms PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_algorithms)


add_library(${PROJECT_NAME}_microcanonical_reference_models
  src/microcanonical_reference_models.cpp)
set_target_properties(${PROJECT_NAME}_microcanonical_reference_models
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_microcanonical_reference_models PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE
  ${PROJECT_NAME}_microcanonical_reference_models)

add_library(${PROJECT_NAME}_type_lists src/type_lists.cpp)
set_target_properties(${PROJECT_NAME}_type_lists
  PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(${PROJECT_NAME}_type_lists PRIVATE
  reticula fmt Metal pybind11::pybind11)
target_link_libraries(reticula_ext PRIVATE ${PROJECT_NAME}_type_lists)

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
