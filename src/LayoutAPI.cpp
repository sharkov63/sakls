#include "sakls/LayoutAPI.hpp"

using namespace sakls;

///===---------------------------------------------------------------------===//
/// LayoutAPIException
///===---------------------------------------------------------------------===//

LayoutAPIException::LayoutAPIException(std::string explanation)
    : std::runtime_error("Layout API exception: " + explanation) {}

///===---------------------------------------------------------------------===//
/// LayoutAPIRef
///===---------------------------------------------------------------------===//

LayoutAPIRef::LayoutAPIRef(sakls_LayoutAPI cAPI) : cAPI(cAPI) {}

LayoutID LayoutAPIRef::getLayout() const {
  LayoutID layout;
  if (cAPI.getLayout(cAPI.impl, &layout))
    throw LayoutAPIException("getLayout failed");
  return layout;
}

void LayoutAPIRef::setLayout(LayoutID layout) {
  if (cAPI.setLayout(cAPI.impl, layout))
    throw LayoutAPIException("setLayout failed");
}

LayoutID LayoutAPIRef::getDefaultLayout() const { return cAPI.defaultLayout; }

void LayoutAPIRef::destroy() { cAPI.destroy(cAPI.impl); }
