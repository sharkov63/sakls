cmake_minimum_required(VERSION 3.16.0)

# ------------------------------------------------------------------------------
# SAKLS project
# ------------------------------------------------------------------------------
set(SAKLS_VERSION_MAJOR 0)
set(SAKLS_VERSION_MINOR 1)
set(SAKLS_VERSION_PATCH 0)
set(SAKLS_VERSION
    ${SAKLS_VERSION_MAJOR}.${SAKLS_VERSION_MINOR}.${SAKLS_VERSION_PATCH})
message(STATUS "Configuring SAKLS ${SAKLS_VERSION}")

project(
  SAKLS
  VERSION ${SAKLS_VERSION}
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SAKLS_PROJECT_DIR ${PROJECT_SOURCE_DIR})
set(SAKLS_INCLUDE_DIRS ${SAKLS_PROJECT_DIR}/include)

# ------------------------------------------------------------------------------
# Third-party dependencies
# ------------------------------------------------------------------------------
add_subdirectory(third-party/cereal)
add_subdirectory(third-party/doctest)
add_subdirectory(third-party/dylib)

# ------------------------------------------------------------------------------
# SAKLS_API C interface library
# ------------------------------------------------------------------------------
add_library(SAKLS_API INTERFACE)
target_include_directories(SAKLS_API INTERFACE ${SAKLS_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# SAKLS shared library
# ------------------------------------------------------------------------------
add_library(SAKLS SHARED src/Engine.cpp src/LayoutAPI.cpp)
target_include_directories(SAKLS PUBLIC ${SAKLS_INCLUDE_DIRS})
target_link_libraries(SAKLS PUBLIC cereal)
target_link_libraries(SAKLS PRIVATE dylib)

# ------------------------------------------------------------------------------
# SAKLS unit-tests
# ------------------------------------------------------------------------------
option(SAKLS_BUILD_TESTS "Build tests" OFF)
if(SAKLS_BUILD_TESTS)
  add_subdirectory(unittests)
endif()
