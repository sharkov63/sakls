#include "MockLayoutBackend.hpp"

#include <ranges>

using namespace sakls;
using namespace sakls::unittests;

///===---------------------------------------------------------------------===//
/// MockLayoutBackend
///===---------------------------------------------------------------------===//

MockLayoutBackend::MockLayoutBackend(
    std::vector<LayoutDescription> layouts) noexcept
    : layouts(layouts), currentLayout(0) {}

static std::vector<LayoutDescription> numToLayouts(size_t layoutNum) {
  auto view = std::views::iota(0ul, layoutNum) |
              std::views::transform([](auto layoutID) -> LayoutDescription {
                return LayoutDescription{"layout" + std::to_string(layoutID)};
              }) |
              std::views::common;
  return std::vector(view.begin(), view.end());
}

MockLayoutBackend::MockLayoutBackend(size_t layoutNum) noexcept
    : MockLayoutBackend(numToLayouts(layoutNum)) {}

MockLayoutBackend::~MockLayoutBackend() = default;

LayoutID MockLayoutBackend::getDefaultLayout() const noexcept { return 0; }

LayoutID MockLayoutBackend::getLayout() const noexcept { return currentLayout; }

void MockLayoutBackend::setLayout(LayoutID layout) noexcept {
  currentLayout = layout;
}

std::vector<LayoutDescription> MockLayoutBackend::allLayouts() noexcept {
  return layouts;
}
