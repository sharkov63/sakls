# List of all layout backends in SAKLS repository
set(SAKLS_ALL_LAYOUT_BACKENDS "xkb-switch")

set(SAKLS_ENABLE_LAYOUT_BACKENDS
    ""
    CACHE STRING "Semicolon-separated list of SAKLS layout backends to build \
      (${SAKLS_ALL_LAYOUT_BACKENDS})")

# ------------------------------------------------------------------------------
# xkb-switch SAKLS layout backend
# ------------------------------------------------------------------------------
set(SAKLS_XKB_SWITCH_ENABLED "xkb-switch" IN_LIST SAKLS_ENABLE_LAYOUT_BACKENDS)
add_subdirectory(XkbSwitch)
if(SAKLS_XKB_SWITCH_ENABLED)
  target_link_libraries(SAKLS PRIVATE SAKLS_XkbSwitch)
else()
  target_link_libraries(SAKLS PRIVATE SAKLS_XkbSwitch_Stub)
endif()
