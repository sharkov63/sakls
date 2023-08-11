cmake_minimum_required(VERSION 3.16.0)

# ------------------------------------------------------------------------------
# SAKLS (Syntax-Aware Keyboard Layout Switching) project
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

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SAKLS_PROJECT_DIR ${PROJECT_SOURCE_DIR})
set(SAKLS_THIRD_PARTY_DIR ${SAKLS_PROJECT_DIR}/third-party)

# ------------------------------------------------------------------------------
# SAKLS_CAPI C interface library
# ------------------------------------------------------------------------------
add_subdirectory(capi)

# ------------------------------------------------------------------------------
# SAKLS shared library
# ------------------------------------------------------------------------------
option(SAKLS_BUILD_LIB "Build SAKLS shared library" ON)
if(SAKLS_BUILD_LIB)
  add_subdirectory(lib)
endif()

# ------------------------------------------------------------------------------
# SAKLS unit-tests
# ------------------------------------------------------------------------------
option(SAKLS_BUILD_TESTS "Build tests" OFF)
if(SAKLS_BUILD_LIB AND SAKLS_BUILD_TESTS)
  add_subdirectory(unittests)
endif()
