#ifndef SAKLS_UNITTESTS_MOCK_LAYOUT_API_HPP
#define SAKLS_UNITTESTS_MOCK_LAYOUT_API_HPP

#include "sakls/LayoutAPI.h"
#include "sakls/LayoutAPI.hpp"

#include <string>
#include <vector>

namespace sakls::unittests {

/// Mock implementation of Layout API for unit-testing.
class MockLayoutAPI {
  std::vector<std::string> layoutNames;
  std::vector<LayoutDescription> layouts;

  LayoutID currentLayout;
  sakls_LayoutAPI cAPI;

public:
  /// Create with provided layout names.
  MockLayoutAPI(std::vector<std::string> layoutNames);

  /// Create with \p layoutNum layouts named "layout0", "layout1" and so on.
  explicit MockLayoutAPI(size_t layoutNum = 2);

  /// Get C++ Layout API reference.
  LayoutAPIRef getAPI() const;

  /// Get C Layout API reference.
  sakls_LayoutAPI getCAPI() const;

  /// Get current keyboard layout.
  LayoutID getLayout() const;

  /// Set current keyboard layout.
  void setLayout(LayoutID layout);
};

} // namespace sakls::unittests

#endif
