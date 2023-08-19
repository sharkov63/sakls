///
/// \file
/// This file implements xkb-switch layout backend,
/// using kb::XKeyboard class from xkb-switch.
///
#include "sakls/Layout.hpp"
#include "sakls/LayoutBackends/XkbSwitch.hpp"

#include "XKeyboard.hpp"

using namespace sakls;
using namespace sakls::xkbswitch;

namespace {

class Backend final : public ILayoutBackend {
  kb::XKeyboard xKeyboard;

public:
  Backend(size_t verbose) : xKeyboard(verbose) {
    try {
      xKeyboard.open_display();
    } catch (const std::runtime_error &error) {
      throw LayoutBackendError(
          std::string("Failed to construct xkb-switch layout backend:\n") +
          error.what());
    }
  }

  virtual ~Backend() override = default;

  virtual LayoutID getDefaultLayout() const noexcept override { return 0; }

  virtual LayoutID getLayout() const noexcept override {
    return xKeyboard.get_group();
  }

  virtual void setLayout(LayoutID layout) override {
    try {
      xKeyboard.set_group(layout);
    } catch (...) {
      throw LayoutBackendError(
          "Failed to setLayout in xkb-switch layout backend.");
    }
  }

  virtual std::vector<LayoutDescription> allLayouts() override {
    std::vector<std::string> layoutNames;
    try {
      xKeyboard.build_layout(layoutNames);
    } catch (const std::runtime_error &error) {
      throw LayoutBackendError(
          std::string(
              "Failed to get layout list from xkb-switch layout backend:\n") +
          error.what());
    }
    size_t layoutsNum = layoutNames.size();
    std::vector<LayoutDescription> layouts(layoutsNum);
    for (LayoutID layoutID = 0; layoutID < layoutsNum; ++layoutID)
      layouts[layoutID].type = std::move(layoutNames[layoutID]);
    return layouts;
  }
};

} // namespace

std::unique_ptr<ILayoutBackend> xkbswitch::createLayoutBackend(size_t verbose) {
  return std::make_unique<Backend>(verbose);
}
