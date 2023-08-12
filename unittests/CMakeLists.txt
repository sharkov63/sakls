set(SAKLS_UNITTESTS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# ------------------------------------------------------------------------------
# doctest dependency
# ------------------------------------------------------------------------------
add_subdirectory(third-party/doctest)

# ------------------------------------------------------------------------------
# SAKLS unit-tests executable
# ------------------------------------------------------------------------------
add_executable(SAKLS_Unittests EngineTest.cpp EngineTests.cpp Main.cpp
                               MockLayoutBackend.cpp SchemaSerialization.cpp)
target_link_libraries(SAKLS_Unittests PRIVATE SAKLS doctest)
target_include_directories(SAKLS_Unittests
                           PRIVATE ${SAKLS_UNITTESTS_BINARY_DIR})

# ------------------------------------------------------------------------------
# Target to run unit tests
# ------------------------------------------------------------------------------
add_custom_target(
  SAKLS_Unittests+Run
  ./SAKLS_Unittests
  DEPENDS SAKLS_Unittests
  WORKING_DIRECTORY ${SAKLS_UNITTESTS_BINARY_DIR}
  USES_TERMINAL)
