# ------------------------------------------------------------------------------
# xkb-switch dependency
# ------------------------------------------------------------------------------
add_subdirectory(third-party/xkb-switch)
get_target_property(XKB_SWITCH_SOURCE_DIR xkbswitch SOURCE_DIR)

# ------------------------------------------------------------------------------
# SAKLS xkb-switch layout backend library
# ------------------------------------------------------------------------------
set(SAKLS_XkbSwitch_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SAKLS_XkbSwitch_INCLUDE_DIR ${SAKLS_XkbSwitch_DIR}/include)

add_library(SAKLS_XkbSwitch STATIC src/LayoutBackend.cpp)

target_include_directories(
  SAKLS_XkbSwitch
  PUBLIC ${SAKLS_XkbSwitch_INCLUDE_DIR}
  PRIVATE ${SAKLS_LIB_INCLUDE_DIR})

target_link_libraries(SAKLS_XkbSwitch PRIVATE xkbswitch)
# XKeyboard.hpp is located in src/ dir
target_include_directories(SAKLS_XkbSwitch PRIVATE ${XKB_SWITCH_SOURCE_DIR}/src)

# Link xkb-switch layout backend with main SAKLS shared library.
target_link_libraries(SAKLS PRIVATE SAKLS_XkbSwitch)
