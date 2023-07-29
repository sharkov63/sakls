#include "sakls/LayoutAPI.hpp"
#include "sakls/CAPI/LayoutPlugin.h"

#include "dylib.hpp"

using namespace sakls;

///===---------------------------------------------------------------------===//
/// LayoutAPIException
///===---------------------------------------------------------------------===//

LayoutAPIException::LayoutAPIException(std::string explanation)
    : std::runtime_error("Layout API exception: " + explanation) {}

///===---------------------------------------------------------------------===//
/// LayoutAPIRef
///===---------------------------------------------------------------------===//

LayoutAPIRef::LayoutAPIRef() : cAPI{.impl = nullptr} {}

LayoutAPIRef::LayoutAPIRef(sakls_LayoutAPI cAPI) : cAPI(cAPI) {}

bool LayoutAPIRef::initialized() const { return cAPI.impl; }

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

void LayoutAPIRef::destroy() {
  if (!initialized())
    return;
  cAPI.destroy(cAPI.impl);
  cAPI.impl = nullptr;
}

///===---------------------------------------------------------------------===//
/// LayoutAPI
///===---------------------------------------------------------------------===//

LayoutAPI::LayoutAPI(sakls_LayoutAPI cAPI) : LayoutAPIRef(std::move(cAPI)) {}

LayoutAPI::~LayoutAPI() { destroy(); }

///===---------------------------------------------------------------------===//
/// Layout Plugin loading
///===---------------------------------------------------------------------===//

namespace {

/// An implementation of layout API loaded from a layout plugin.
/// This object owns the layout API as well as the connection to the opened
/// shared plugin.
///
/// Loading the layout plugin is implemented in a portable fashion using dylib
/// third-party library.
class LayoutPlugin : public LayoutAPI {
  dylib lib;

public:
  LayoutPlugin(sakls_LayoutAPI cAPI, dylib &&lib)
      : LayoutAPI(cAPI), lib(std::move(lib)) {}

  virtual ~LayoutPlugin() {
    destroy(); // we should destroy Layout API before destroying the lib
  }
};

} // namespace

template <typename... Args>
static std::unique_ptr<LayoutAPI> load(void *producerConfig, Args &&...args) {
  try {
    dylib lib(std::forward<Args>(args)...);
    if (!lib.has_symbol("sakls_getLayoutPluginInfo"))
      throw LayoutAPIException(
          "layout plugin is invalid: no sakls_getLayoutPluginInfo symbol.");
    auto *getPluginInfo = lib.get_function<decltype(sakls_getLayoutPluginInfo)>(
        "sakls_getLayoutPluginInfo");
    sakls_LayoutPluginInfo pluginInfo = (*getPluginInfo)();
    if (pluginInfo.apiVersion != SAKLS_LAYOUT_API_VERSION)
      throw LayoutAPIException(
          "layout plugin understands wrong layout API version " +
          std::to_string(pluginInfo.apiVersion) + "; expected " +
          std::to_string(SAKLS_LAYOUT_API_VERSION));
    sakls_LayoutAPI cAPI = pluginInfo.produceLayoutAPIImpl(producerConfig);
    return std::make_unique<LayoutPlugin>(cAPI, std::move(lib));
  } catch (const dylib::exception &error) {
    throw LayoutAPIException(std::string("Failed to load layout plugin: ") +
                             error.what());
  }
}

std::unique_ptr<LayoutAPI>
LayoutAPI::loadPlugin(const std::filesystem::path &plugin,
                      void *producerConfig) {
  return load(producerConfig, plugin);
}
std::unique_ptr<LayoutAPI>
LayoutAPI::loadPlugin(const std::filesystem::path &dir,
                      const std::string &libName, void *producerConfig) {
  return load(producerConfig, dir, libName);
}
std::unique_ptr<LayoutAPI> LayoutAPI::loadPlugin(const std::string &libName,
                                                 void *producerConfig) {
  return load(producerConfig, libName);
}
