# ------------------------------------------------------------------------------
# Generated header containing SAKLS unittests binary directory path
# ------------------------------------------------------------------------------
set(SAKLS_UNITTESTS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
configure_file(BinaryDir.h.in ${CMAKE_CURRENT_BINARY_DIR}/BinaryDir.h)

# ------------------------------------------------------------------------------
# doctest dependency
# ------------------------------------------------------------------------------
add_subdirectory(${SAKLS_THIRD_PARTY_DIR}/doctest
                 ${SAKLS_UNITTESTS_BINARY_DIR}/third-party/doctest)

# ------------------------------------------------------------------------------
# SAKLS mock layout plugin
# ------------------------------------------------------------------------------
add_library(SAKLS_MockLayoutPlugin MODULE MockLayoutPlugin.cpp
                                          MockLayoutAPI.cpp)
target_link_libraries(SAKLS_MockLayoutPlugin PRIVATE SAKLS SAKLS_CAPI)

# ------------------------------------------------------------------------------
# SAKLS unit-tests executable
# ------------------------------------------------------------------------------
add_executable(
  SAKLS_Unittests EngineTest.cpp EngineTests.cpp LayoutPluginTest.cpp Main.cpp
                  MockLayoutAPI.cpp SchemaSerialization.cpp)
target_link_libraries(SAKLS_Unittests PRIVATE SAKLS doctest)
target_include_directories(SAKLS_Unittests
                           PRIVATE ${SAKLS_UNITTESTS_BINARY_DIR})
add_dependencies(SAKLS_Unittests SAKLS_MockLayoutPlugin)

# ------------------------------------------------------------------------------
# Target to run unit tests
# ------------------------------------------------------------------------------
add_custom_target(
  SAKLS_Unittests+Run
  ./SAKLS_Unittests
  DEPENDS SAKLS_Unittests
  WORKING_DIRECTORY ${SAKLS_UNITTESTS_BINARY_DIR}
  USES_TERMINAL)
