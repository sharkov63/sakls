///
/// \file XkbSwitchCAPI.cpp
/// Implements C API of xkb-switch layout backend.
///
#include "sakls-c/LayoutBackends/XkbSwitch.h"
#include "sakls/Layout.hpp"
#include "sakls/LayoutBackends/XkbSwitch.hpp"

using namespace sakls;

extern "C" int sakls_XkbSwitch_createLayoutBackend(void **layoutBackend) {
  try {
    *layoutBackend = xkbswitch::createLayoutBackend().release();
    return 0;
  } catch (...) {
  }
  return -1;
}

extern "C" void sakls_XkbSwitch_deleteLayoutBackend(void *layoutBackend) {
  if (!layoutBackend)
    return;
  delete reinterpret_cast<ILayoutBackend *>(layoutBackend);
}
