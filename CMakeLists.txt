cmake_minimum_required(VERSION 3.11)

project(dag_python LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  dag
  GIT_REPOSITORY https://github.com/arashbm/dag.git
  GIT_TAG 89950b2)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 8.0.1)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.9.0)

FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/brunocodutra/metal.git
  GIT_TAG 2.1.3)

FetchContent_GetProperties(pybind11)
if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
endif()

FetchContent_MakeAvailable(dag fmt metal)

add_library(python_dag_static_edges src/static_edges.cpp)
target_link_libraries(python_dag_static_edges PRIVATE
  dag fmt Metal pybind11::pybind11)

add_library(python_dag_static_networks src/static_networks.cpp)
target_link_libraries(python_dag_static_networks PRIVATE
  dag fmt Metal pybind11::pybind11)

add_library(python_dag_temporal_edges src/temporal_edges.cpp)
target_link_libraries(python_dag_temporal_edges PRIVATE
  dag fmt Metal pybind11::pybind11)

add_library(python_dag_temporal_networks src/temporal_networks.cpp)
target_link_libraries(python_dag_temporal_networks PRIVATE
  dag fmt Metal pybind11::pybind11)

add_library(python_dag_generators src/generators.cpp)
target_link_libraries(python_dag_generators PRIVATE
  dag fmt Metal pybind11::pybind11)

add_library(python_dag_algorithms src/algorithms.cpp)
target_link_libraries(python_dag_algorithms PRIVATE
  dag fmt Metal pybind11::pybind11)

pybind11_add_module(dag_ext src/main.cpp)
target_link_libraries(dag_ext PRIVATE
    dag fmt Metal
    python_dag_static_networks python_dag_static_edges
    python_dag_temporal_edges python_dag_temporal_networks
    python_dag_generators python_dag_algorithms)
