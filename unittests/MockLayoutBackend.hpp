///
/// \file MockLayoutBackend.hpp
/// Mock layout backend for unit-testing.
///
#ifndef SAKLS_UNITTESTS_MOCK_LAYOUT_BACKEND_HPP
#define SAKLS_UNITTESTS_MOCK_LAYOUT_BACKEND_HPP

#include "sakls/Layout.hpp"

#include <vector>

namespace sakls::unittests {

/// Mock layout backend for unit-testing.
class MockLayoutBackend : public ILayoutBackend {
  std::vector<LayoutDescription> layouts;
  LayoutID currentLayout;

public:
  /// Create with provided layout names.
  explicit MockLayoutBackend(std::vector<LayoutDescription> layouts) noexcept;

  /// Create with \p layoutNum layouts named "layout0", "layout1" and so on.
  explicit MockLayoutBackend(size_t layoutNum = 2) noexcept;

  virtual ~MockLayoutBackend() override;

  virtual LayoutID getDefaultLayout() const noexcept override;

  virtual LayoutID getLayout() const noexcept override;

  virtual void setLayout(LayoutID layout) noexcept override;

  virtual std::vector<LayoutDescription> allLayouts() noexcept override;
};

} // namespace sakls::unittests

#endif
