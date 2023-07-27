set(SAKLS_UNITTESTS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
configure_file(BinaryDir.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/SAKLSUnittestsBinaryDir.h)

add_library(SAKLSMockLayoutPlugin MODULE MockLayoutPlugin.cpp MockLayoutAPI.cpp)
target_link_libraries(SAKLSMockLayoutPlugin PRIVATE SAKLSInterface)

add_executable(
  SAKLSUnittests
  EngineTest.cpp
  EngineTests.cpp
  LayoutPluginTest.cpp
  Main.cpp
  MockLayoutAPI.cpp
  MockSyntaxAPI.cpp
  SchemaSerialization.cpp)
target_link_libraries(SAKLSUnittests PRIVATE SAKLS doctest)
target_include_directories(SAKLSUnittests PRIVATE ${SAKLS_UNITTESTS_BINARY_DIR})
add_dependencies(SAKLSUnittests SAKLSMockLayoutPlugin)
