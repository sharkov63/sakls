# List of all layout backends in SAKLS repository
set(SAKLS_ALL_LAYOUT_BACKENDS "xkb-switch")

set(SAKLS_ENABLE_LAYOUT_BACKENDS
    ""
    CACHE STRING "Semicolon-separated list of SAKLS layout backends to build \
      (${SAKLS_ALL_LAYOUT_BACKENDS})")

# ------------------------------------------------------------------------------
# xkb-switch SAKLS layout backend
# ------------------------------------------------------------------------------
if("xkb-switch" IN_LIST SAKLS_ENABLE_LAYOUT_BACKENDS)
  add_subdirectory(xkb-switch)
endif()
