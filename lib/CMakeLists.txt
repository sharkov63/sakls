# ------------------------------------------------------------------------------
# SAKLS shared library
# ------------------------------------------------------------------------------
set(SAKLS_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SAKLS_LIB_INCLUDE_DIR ${SAKLS_LIB_DIR}/include)
add_library(SAKLS SHARED src/Engine.cpp src/LayoutAPI.cpp)
target_include_directories(SAKLS PUBLIC ${SAKLS_LIB_INCLUDE_DIR})
target_link_libraries(SAKLS PUBLIC SAKLS_CAPI cereal)
target_link_libraries(SAKLS PRIVATE dylib)
