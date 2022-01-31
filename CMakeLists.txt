cmake_minimum_required(VERSION 3.11)

project(dag_python LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  dag
  GIT_REPOSITORY https://github.com/arashbm/dag.git
  GIT_TAG 210f276)

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
  GIT_TAG 2.1.3)

FetchContent_GetProperties(pybind11)
if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
endif()

FetchContent_MakeAvailable(dag fmt metal)


set(total_parts 10)

pybind11_add_module(dag_ext src/main.cpp)

target_link_libraries(dag_ext PRIVATE dag fmt Metal)

add_library(python_dag_random_state src/random_state.cpp)
target_link_libraries(python_dag_random_state PRIVATE
  dag fmt Metal pybind11::pybind11)
target_link_libraries(dag_ext PRIVATE python_dag_random_state)


function(add_partial_library name source parts)
  foreach(n RANGE ${parts})
    add_library(python_dag_${name}_${n} ${source})
    target_compile_definitions(python_dag_${name}_${n} PRIVATE
      BUILD_TOTAL_PARTS=${parts} BUILD_CURRENT_PART=${n})
    target_link_libraries(python_dag_${name}_${n} PRIVATE ${ARGN})
    target_link_libraries(dag_ext PRIVATE python_dag_${name}_${n})
  endforeach()
endfunction()

add_partial_library(temporal_edges src/temporal_edges.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)

add_partial_library(temporal_hyperedges src/temporal_hyperedges.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)

add_partial_library(static_edges src/static_edges.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)

add_partial_library(static_hyperedges src/static_hyperedges.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)


add_partial_library(networks src/networks.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)

add_partial_library(generators src/generators.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)


add_partial_library(random_networks src/random_networks.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)


add_partial_library(components src/components.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)


add_partial_library(algorithms src/algorithms.cpp ${total_parts}
  dag fmt Metal pybind11::pybind11)
