#include "sakls/LayoutAPI.hpp"

using namespace sakls;

LayoutAPI::LayoutAPI(sakls_LayoutAPI &&cAPI) : cAPI(std::move(cAPI)) {}

LayoutAPI::~LayoutAPI() { cAPI.destroy(cAPI.impl); }

LayoutID LayoutAPI::getLayout() const {
  LayoutID layout = cAPI.getLayout(cAPI.impl);
  if (layout < 0)
    throw LayoutAPIException();
  return layout;
}

void LayoutAPI::setLayout(LayoutID layout) {
  if (cAPI.setLayout(cAPI.impl, layout))
    throw LayoutAPIException();
}
