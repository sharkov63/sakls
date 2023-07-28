///
/// \file MockLayoutPlugin.cpp
/// This file contains a mock layout plugin library implementation.
///
#include "sakls/LayoutPlugin.h"

#include "MockLayoutAPI.hpp"

using namespace sakls::unittests;

static void destroy(void *impl) {
  if (!impl)
    abort(); // catch invalid destructions
  delete reinterpret_cast<MockLayoutAPI *>(impl);
}

static sakls_LayoutAPI produceLayoutAPIImpl(void *producerConfig) {
  MockLayoutAPI *layoutAPI = new MockLayoutAPI();
  sakls_LayoutAPI cAPI = layoutAPI->getCAPI();
  cAPI.destroy = destroy;
  if (producerConfig) {
    cAPI.defaultLayout = *reinterpret_cast<sakls_LayoutID *>(producerConfig);
  }
  return cAPI;
}

extern "C" struct sakls_LayoutPluginInfo sakls_getLayoutPluginInfo() {
  return {
      .apiVersion = SAKLS_LAYOUT_API_VERSION,
      .pluginName = "SAKLS Mock Layout Plugin",
      .pluginVersion = "v0.0.0",
      .produceLayoutAPIImpl = produceLayoutAPIImpl,
  };
}
