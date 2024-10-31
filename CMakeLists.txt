cmake_minimum_required(VERSION 3.15...3.27)
project(nanobind_example)

# Find Python and required components
if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()


find_package(Python 3.8 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)
# message(STATUS "Python executable: ${PYTHON_EXECUTABLE}")

# Set default build type to Release
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)

  # echo "nanobind_ROOT: ${nanobind_ROOT}"
  message(STATUS "nanobind_ROOT: ${nanobind_ROOT}")

# set(nanobind_ROOT /home/grl/repo/micromamba/envs/py38/lib/python3.8/site-packages/nanobind/cmake)
find_package(nanobind CONFIG REQUIRED)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/__init__.py") # Creates an empty file

nanobind_add_module(my_ext my_ext.cpp)

