cmake_minimum_required(VERSION 3.16.0)

project(SAKLS)

set(SAKLS_DIR ${PROJECT_SOURCE_DIR})
set(SAKLS_INCLUDE_DIRS ${SAKLS_DIR}/include)

# SaklsAPI interface library.
add_library(SaklsAPI INTERFACE)
target_include_directories(SaklsAPI INTERFACE ${SAKLS_INCLUDE_DIRS})
