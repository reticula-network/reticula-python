cmake_minimum_required(VERSION 3.11)

project(dag_python LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include(FetchContent)
FetchContent_Declare(
  dag
  GIT_REPOSITORY https://github.com/arashbm/dag.git
  GIT_TAG 427fe93)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 8.1.1)

FetchContent_Declare(
  nanobind
  GIT_REPOSITORY https://github.com/wjakob/nanobind.git
  GIT_TAG ce1d6f3)

FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/brunocodutra/metal.git
  GIT_TAG v2.1.4)

if (SKBUILD)
  message(WARNING "SKBUILD is set")
  # Constrain FindPython to find the Python version used by scikit-build
  set(Python_VERSION "${PYTHON_VERSION_STRING}")
  set(Python_EXECUTABLE "${PYTHON_EXECUTABLE}")
  set(Python_INCLUDE_DIR "${PYTHON_INCLUDE_DIR}")
  set(Python_LIBRARIES "${PYTHON_LIBRARY}")
elseif (MSVC)
  # MSVC needs a little extra help finding the Python library
  find_package(PythonInterp)
  find_package(Python)
endif()

find_package(Python 3.9 COMPONENTS Interpreter Development.Module REQUIRED)


FetchContent_GetProperties(nanobind)
if(NOT nanobind_POPULATED)
    FetchContent_Populate(nanobind)
    add_subdirectory(${nanobind_SOURCE_DIR} ${nanobind_BINARY_DIR})
endif()

FetchContent_MakeAvailable(dag fmt metal)


nanobind_add_module(dag_ext
  src/main.cpp
  src/scalar_types.cpp
  src/random_state.cpp
  src/interval_sets.cpp
  src/temporal_edges.cpp src/temporal_hyperedges.cpp
  src/static_edges.cpp src/static_hyperedges.cpp
  src/networks.cpp
  src/temporal_adjacency.cpp
  src/implicit_event_graphs.cpp
  src/implicit_event_graph_components.cpp
  src/generators.cpp
  src/random_networks.cpp
  src/temporal_clusters.cpp src/temporal_cluster_containers.cpp
  src/components.cpp src/component_containers.cpp
  src/io.cpp
  src/algorithms.cpp src/algorithms/directed.cpp src/algorithms/undirected.cpp src/algorithms/temporal.cpp
  src/microcanonical_reference_models.cpp)
target_link_libraries(dag_ext PRIVATE dag fmt Metal cxx_std_20)


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
