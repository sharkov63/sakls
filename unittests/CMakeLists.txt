add_executable(
  SAKLSUnittests EngineTest.cpp EngineTests.cpp Main.cpp MockLayoutAPI.cpp
                 MockSyntaxAPI.cpp SchemaSerialization.cpp)
target_link_libraries(SAKLSUnittests PRIVATE SAKLS doctest)
