if(SAKLS_XKB_SWITCH_ENABLED)
  # ------------------------------------------------------------------------------
  # xkb-switch dependency
  # ------------------------------------------------------------------------------
  add_subdirectory(third-party/xkb-switch)
  get_target_property(XKB_SWITCH_SOURCE_DIR xkbswitch SOURCE_DIR)

  # ------------------------------------------------------------------------------
  # SAKLS xkb-switch layout backend library
  # ------------------------------------------------------------------------------
  add_library(SAKLS_XkbSwitch OBJECT XkbSwitchBackend.cpp XkbSwitchCAPI.cpp)
  set_target_properties(SAKLS_XkbSwitch PROPERTIES POSITION_INDEPENDENT_CODE ON)

  target_include_directories(SAKLS_XkbSwitch PRIVATE ${SAKLS_INCLUDE_DIR})

  target_link_libraries(SAKLS_XkbSwitch PRIVATE xkbswitch)
  # XKeyboard.hpp is located in src/ dir
  target_include_directories(SAKLS_XkbSwitch
                             PRIVATE ${XKB_SWITCH_SOURCE_DIR}/src)
else()
  # ------------------------------------------------------------------------------
  # stub library when xkb-switch layout backend is not built
  # ------------------------------------------------------------------------------
  add_library(SAKLS_XkbSwitch_Stub OBJECT XkbSwitchStub.cpp XkbSwitchCAPI.cpp)
  set_target_properties(SAKLS_XkbSwitch_Stub
                        PROPERTIES POSITION_INDEPENDENT_CODE ON)
  target_include_directories(SAKLS_XkbSwitch_Stub PRIVATE ${SAKLS_INCLUDE_DIR})
endif()
