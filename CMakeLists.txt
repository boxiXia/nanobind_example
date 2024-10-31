cmake_minimum_required(VERSION 3.15...3.27)
project(nanobind_example
  LANGUAGES C CXX)
# set (CMAKE_CXX_STANDARD 17) # optional

set(CMAKE_POSITION_INDEPENDENT_CODE ON) 


# Find Python and required components
if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.8 
  REQUIRED COMPONENTS Interpreter ${DEV_MODULE}
  OPTIONAL_COMPONENTS Development.SABIModule)

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
find_package(nanobind CONFIG REQUIRED)


find_package(Eigen3 CONFIG REQUIRED)


file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/__init__.py") # Creates an empty file

nanobind_add_module(
  # Name of the extension
  my_ext 

  # shared libnanobind across libraries
  NB_SHARED # or NB_STATIC

  # Target the stable ABI for Python 3.12+, which reduces
  # the number of binary wheels that must be built. This
  # does nothing on older Python versions
  STABLE_ABI

  # Source code goes here
  ${CMAKE_CURRENT_SOURCE_DIR}/my_ext.cpp
)

target_link_libraries(my_ext PRIVATE Eigen3::Eigen)
