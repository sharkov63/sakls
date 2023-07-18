cmake_minimum_required(VERSION 3.16.0)

project(SAKLS)

set(SAKLS_DIR ${PROJECT_SOURCE_DIR})
set(SAKLS_INCLUDE_DIRS ${SAKLS_DIR}/include)

# third-party
add_subdirectory(third-party/doctest)

# SaklsAPI interface library.
add_library(SaklsAPI INTERFACE)
target_include_directories(SaklsAPI INTERFACE ${SAKLS_INCLUDE_DIRS})

# SAKLS shared library.
add_library(SAKLS SHARED src/Engine.cpp src/EngineAPI.cpp src/LayoutAPI.cpp
                         src/SyntaxAPI.cpp)
target_include_directories(SAKLS PRIVATE ${SAKLS_INCLUDE_DIRS})

# Unit-tests executable.
add_subdirectory(unittests)
