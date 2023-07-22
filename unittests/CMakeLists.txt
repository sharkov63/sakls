add_executable(
  SaklsUnitTests EngineTest.cpp EngineTests.cpp Main.cpp MockLayoutAPI.cpp
                 MockSyntaxAPI.cpp SchemaSerialization.cpp)
target_link_libraries(SaklsUnitTests PRIVATE SAKLS doctest)
