#include "sakls/LayoutAPI.hpp"

using namespace sakls;

///===---------------------------------------------------------------------===//
/// LayoutAPIRef
///===---------------------------------------------------------------------===//

LayoutAPIRef::LayoutAPIRef(sakls_LayoutAPI cAPI) : cAPI(cAPI) {}

LayoutID LayoutAPIRef::getLayout() const {
  LayoutID layout = cAPI.getLayout(cAPI.impl);
  if (layout < 0)
    throw LayoutAPIException();
  return layout;
}

void LayoutAPIRef::setLayout(LayoutID layout) {
  if (cAPI.setLayout(cAPI.impl, layout))
    throw LayoutAPIException();
}

void LayoutAPIRef::destroy() { cAPI.destroy(cAPI.impl); }
