///
/// \file LayoutPluginTest.cpp
/// This file tests layout plugin loading functionality.
///
#include "BinaryDir.h"
#include "doctest/doctest.h"
#include "sakls/LayoutAPI.hpp"

using namespace sakls;

namespace {

TEST_CASE("Layout Plugin") {
  LayoutAPI layoutAPI =
      LayoutAPI::loadPlugin(std::filesystem::path(SAKLS_UNITTESTS_BINARY_DIR),
                            "SAKLS_MockLayoutPlugin", nullptr);
  CHECK(layoutAPI.getLayout() == 0);
  layoutAPI.setLayout(1);
  CHECK(layoutAPI.getLayout() == 1);
  layoutAPI.setLayout(0);
  CHECK(layoutAPI.getLayout() == 0);
  CHECK(layoutAPI.getDefaultLayout() == 0);
  CHECK(layoutAPI.initialized());
  layoutAPI.destroy();
  CHECK(!layoutAPI.initialized());
}

TEST_CASE("Layout Plugin: pass producerConfig") {
  LayoutID defaultLayout = 1;
  auto layoutAPI =
      LayoutAPI::loadPlugin(std::filesystem::path(SAKLS_UNITTESTS_BINARY_DIR),
                            "SAKLS_MockLayoutPlugin", &defaultLayout);
  CHECK(layoutAPI.getDefaultLayout() == 1);
}

} // namespace
