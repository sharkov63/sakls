add_executable(SaklsUnitTests Main.cpp SchemaSerialization.cpp)
target_link_libraries(SaklsUnitTests PRIVATE SAKLS doctest)
