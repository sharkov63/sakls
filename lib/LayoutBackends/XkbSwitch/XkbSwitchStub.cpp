///
/// \file XkbSwitchStub.cpp
/// Stub implementation of xkbswitch::createLayoutBackend,
/// when xkb-switch SAKLS layout backend is not built.
///
#include "sakls/Layout.hpp"
#include "sakls/LayoutBackends/XkbSwitch.hpp"

using namespace sakls;

std::unique_ptr<ILayoutBackend> xkbswitch::createLayoutBackend(size_t) {
  throw LayoutBackendError("xkb-switch layout backend was not built!");
}
