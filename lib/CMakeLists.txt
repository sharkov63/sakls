# ------------------------------------------------------------------------------
# Third-party dependencies
# ------------------------------------------------------------------------------
add_subdirectory(third-party/cereal)

# ------------------------------------------------------------------------------
# SAKLS shared library
# ------------------------------------------------------------------------------
set(SAKLS_LIB_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE PATH "Top directory of SAKLS shared library" FORCE)
set(SAKLS_LIB_INCLUDE_DIR
    ${SAKLS_LIB_DIR}/include
    CACHE PATH "Include directory of SAKLS shared library" FORCE)
add_library(SAKLS SHARED src/Engine.cpp)
target_include_directories(SAKLS PUBLIC ${SAKLS_LIB_INCLUDE_DIR})
target_link_libraries(SAKLS PUBLIC SAKLS_CAPI cereal)
