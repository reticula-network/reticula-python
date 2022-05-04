cmake_minimum_required(VERSION 3.11)

project(dag_python LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  dag
  GIT_REPOSITORY https://github.com/arashbm/dag.git
  GIT_TAG f3cc5d)

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

FetchContent_MakeAvailable(dag fmt metal)


pybind11_add_module(dag_ext src/main.cpp)
target_link_libraries(dag_ext PRIVATE dag fmt Metal)

add_library(${PROJECT_NAME}_scaler_types src/scalar_types.cpp)
target_link_libraries(${PROJECT_NAME}_scaler_types PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_scaler_types)

add_library(${PROJECT_NAME}_random_state src/random_state.cpp)
target_link_libraries(${PROJECT_NAME}_random_state PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_random_state)

add_library(${PROJECT_NAME}_interval_sets src/interval_sets.cpp)
target_link_libraries(${PROJECT_NAME}_interval_sets PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_interval_sets)

add_library(${PROJECT_NAME}_temporal_edges src/temporal_edges.cpp)
target_link_libraries(${PROJECT_NAME}_temporal_edges PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_temporal_edges)

add_library(${PROJECT_NAME}_temporal_hyperedges src/temporal_hyperedges.cpp)
target_link_libraries(${PROJECT_NAME}_temporal_hyperedges PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_temporal_hyperedges)


add_library(${PROJECT_NAME}_static_edges src/static_edges.cpp)
target_link_libraries(${PROJECT_NAME}_static_edges PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_static_edges)

add_library(${PROJECT_NAME}_static_hyperedges src/static_hyperedges.cpp)
target_link_libraries(${PROJECT_NAME}_static_hyperedges PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_static_hyperedges)


add_library(${PROJECT_NAME}_networks src/networks.cpp)
target_link_libraries(${PROJECT_NAME}_networks PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_networks)


add_library(${PROJECT_NAME}_temporal_adjacency src/temporal_adjacency.cpp)
target_link_libraries(${PROJECT_NAME}_temporal_adjacency PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_temporal_adjacency)


add_library(${PROJECT_NAME}_implicit_event_graphs src/implicit_event_graphs.cpp)
target_link_libraries(${PROJECT_NAME}_implicit_event_graphs PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_implicit_event_graphs)

add_library(${PROJECT_NAME}_implicit_event_graph_components
  src/implicit_event_graph_components.cpp)
target_link_libraries(${PROJECT_NAME}_implicit_event_graph_components PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE
  ${PROJECT_NAME}_implicit_event_graph_components)

add_library(${PROJECT_NAME}_generators src/generators.cpp)
target_link_libraries(${PROJECT_NAME}_generators PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_generators)


add_library(${PROJECT_NAME}_random_networks src/random_networks.cpp)
target_link_libraries(${PROJECT_NAME}_random_networks PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_random_networks)

add_library(${PROJECT_NAME}_temporal_clusters src/temporal_clusters.cpp)
target_link_libraries(${PROJECT_NAME}_temporal_clusters PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_temporal_clusters)

add_library(${PROJECT_NAME}_temporal_cluster_containers
  src/temporal_cluster_containers.cpp)
target_link_libraries(${PROJECT_NAME}_temporal_cluster_containers PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE
  ${PROJECT_NAME}_temporal_cluster_containers)

add_library(${PROJECT_NAME}_components src/components.cpp)
target_link_libraries(${PROJECT_NAME}_components PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_components)

add_library(${PROJECT_NAME}_component_containers src/component_containers.cpp)
target_link_libraries(${PROJECT_NAME}_component_containers PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_component_containers)

add_library(${PROJECT_NAME}_io src/io.cpp)
target_link_libraries(${PROJECT_NAME}_io PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_io)


add_library(${PROJECT_NAME}_algorithms
  src/algorithms.cpp
  src/algorithms/directed.cpp
  src/algorithms/undirected.cpp
  src/algorithms/temporal.cpp)
target_link_libraries(${PROJECT_NAME}_algorithms PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE ${PROJECT_NAME}_algorithms)


add_library(${PROJECT_NAME}_microcanonical_reference_models
  src/microcanonical_reference_models.cpp)
target_link_libraries(${PROJECT_NAME}_microcanonical_reference_models PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE
  ${PROJECT_NAME}_microcanonical_reference_models)

install(TARGETS dag_ext DESTINATION .)

set(lib_path "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${lib_path}" is_system)
if ("${is_system}" STREQUAL "-1")
    # The following is necessary for installation in a virtual
    # environment `python -m pip venv env`
    set_target_properties(dag_ext PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH TRUE
        INSTALL_RPATH "${lib_path}")
endif()
