# ------------------------------------------------------------------------------
# Doxygen
# ------------------------------------------------------------------------------
option(SAKLS_ENABLE_DOXYGEN "Build Doxygen documentation for SAKLS" OFF)
if(SAKLS_ENABLE_DOXYGEN)
  find_package(Doxygen REQUIRED dot)
  set(DOXYGEN_PROJECT_BRIEF "Syntax-Aware Keyboard Layout Switching")
  set(DOXYGEN_EXCLUDE_PATTERNS "*/third-party/*")
  set(DOXYGEN_SOURCE_BROWSER "YES")
  set(DOXYGEN_EXTRACT_ALL "YES")
  set(DOXYGEN_GENERATE_TAGFILE "sakls.doxytags")
  set(DOXYGEN_STRIP_FROM_PATH ${SAKLS_PROJECT_DIR})
  if(SAKLS_BUILD_LIB)
    list(APPEND DOXYGEN_TAGFILES "${CEREAL_BINARY_DIR}/cereal.doxytags")
  endif()
  doxygen_add_docs(
    SAKLS_Doxygen ${SAKLS_PROJECT_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating SAKLS Doxygen documentation")
endif()
