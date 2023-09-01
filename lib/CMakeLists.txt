# ------------------------------------------------------------------------------
# Third-party dependencies
# ------------------------------------------------------------------------------
add_subdirectory(third-party/cereal)
get_target_property(CEREAL_BINARY_DIR cereal BINARY_DIR)
set(CEREAL_BINARY_DIR
    ${CEREAL_BINARY_DIR}
    PARENT_SCOPE)
set(SPDLOG_BUILD_PIC ON CACHE BOOL "Use PIC in spdlog" FORCE)
add_subdirectory(third-party/spdlog)

# ------------------------------------------------------------------------------
# SAKLS shared library
# ------------------------------------------------------------------------------
add_library(SAKLS SHARED Engine.cpp Schema.cpp)
target_include_directories(SAKLS PUBLIC ${SAKLS_INCLUDE_DIR})
target_link_libraries(SAKLS PUBLIC cereal spdlog::spdlog)

# ------------------------------------------------------------------------------
# Layout backends, linked with SAKLS
# ------------------------------------------------------------------------------
add_subdirectory(LayoutBackends)
