#include "MockLayoutAPI.hpp"

using namespace sakls;
using namespace sakls::unittests;

///===---------------------------------------------------------------------===//
/// MockLayoutAPI
///===---------------------------------------------------------------------===//

static std::vector<LayoutDescription>
namesToDescriptions(std::vector<std::string> &layoutNames) {
  std::vector<LayoutDescription> layouts;
  layouts.reserve(layoutNames.size());
  for (const auto &name : layoutNames)
    layouts.push_back(LayoutDescription{name.c_str()});
  return layouts;
}

MockLayoutAPI::MockLayoutAPI(std::vector<std::string> layoutNames)
    : layoutNames(std::move(layoutNames)),
      layouts(namesToDescriptions(this->layoutNames)), currentLayout(0),
      cAPI{
          .impl = this,
          .defaultLayout = 0,
          .getLayout =
              [](void *impl) {
                return reinterpret_cast<MockLayoutAPI *>(impl)->currentLayout;
              },
          .setLayout =
              [](void *impl, LayoutID layout) {
                reinterpret_cast<MockLayoutAPI *>(impl)->currentLayout = layout;
                return 0;
              },
          .destroy = [](void *) {},
          .layoutListLen = (int)layouts.size(),
          .layoutList = layouts.data(),
      } {}

static std::vector<std::string> numToNames(size_t layoutNum) {
  std::vector<std::string> layoutNames(layoutNum);
  for (size_t layoutID = 0; layoutID < layoutNum; ++layoutID)
    layoutNames[layoutID] = "layout" + std::to_string(layoutID);
  return layoutNames;
}

MockLayoutAPI::MockLayoutAPI(size_t layoutNum)
    : MockLayoutAPI(numToNames(layoutNum)) {}

LayoutAPIRef MockLayoutAPI::getAPI() const { return LayoutAPIRef(cAPI); }

LayoutID MockLayoutAPI::getLayout() const { return currentLayout; }

void MockLayoutAPI::setLayout(LayoutID layout) { currentLayout = layout; }
