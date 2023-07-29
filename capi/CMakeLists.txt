# ------------------------------------------------------------------------------
# SAKLS_CAPI C interface library
# ------------------------------------------------------------------------------
set(SAKLS_CAPI_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SAKLS_CAPI_INCLUDE_DIR ${SAKLS_CAPI_DIR}/include)
add_library(SAKLS_CAPI INTERFACE)
target_include_directories(SAKLS_CAPI INTERFACE ${SAKLS_CAPI_INCLUDE_DIR})
