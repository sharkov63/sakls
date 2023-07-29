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

sakls_LayoutAPI LayoutAPI::release() {
  sakls_LayoutAPI result = cAPI;
  cAPI.impl = nullptr;
  return result;
}

LayoutAPI::~LayoutAPI() { destroy(); }

///===---------------------------------------------------------------------===//
/// Layout Plugin loading
///===---------------------------------------------------------------------===//

namespace {

/// A loaded layout plugin.
///
/// This object owns the layout API as well as the connection to the opened
/// shared plugin.
///
/// Loading the layout plugin is implemented in a portable fashion using dylib
/// third-party library.
struct LayoutPlugin {
  dylib lib;
  sakls_LayoutAPI layoutAPI;

  static int getLayout(void *impl, LayoutID *layout) {
    LayoutPlugin *plugin = reinterpret_cast<LayoutPlugin *>(impl);
    return plugin->layoutAPI.getLayout(plugin->layoutAPI.impl, layout);
  }
  static int setLayout(void *impl, LayoutID layout) {
    LayoutPlugin *plugin = reinterpret_cast<LayoutPlugin *>(impl);
    return plugin->layoutAPI.setLayout(plugin->layoutAPI.impl, layout);
  }
  static void destroy(void *impl) {
    LayoutPlugin *plugin = reinterpret_cast<LayoutPlugin *>(impl);
    plugin->layoutAPI.destroy(plugin->layoutAPI.impl);
    delete plugin;
  }

  sakls_LayoutAPI compose() {
    return {
        .impl = this,
        .defaultLayout = layoutAPI.defaultLayout,
        .getLayout = getLayout,
        .setLayout = setLayout,
        .destroy = destroy,
        .layoutListLen = layoutAPI.layoutListLen,
        .layoutList = layoutAPI.layoutList,
    };
  }
};

} // namespace

template <typename... Args>
static LayoutAPI load(void *producerConfig, Args &&...args) {
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
    LayoutPlugin *plugin = new LayoutPlugin{std::move(lib), cAPI};
    return LayoutAPI(plugin->compose());
  } catch (const dylib::exception &error) {
    throw LayoutAPIException(std::string("Failed to load layout plugin: ") +
                             error.what());
  }
}

LayoutAPI LayoutAPI::loadPlugin(const std::filesystem::path &plugin,
                                void *producerConfig) {
  return load(producerConfig, plugin);
}
LayoutAPI LayoutAPI::loadPlugin(const std::filesystem::path &dir,
                                const std::string &libName,
                                void *producerConfig) {
  return load(producerConfig, dir, libName);
}
LayoutAPI LayoutAPI::loadPlugin(const std::string &libName,
                                void *producerConfig) {
  return load(producerConfig, libName);
}

SAKLS_EXTERN_C_BEGIN

sakls_LayoutAPI sakls_loadLayoutPluginByPath(const char *pluginPath,
                                             void *producerConfig) {
  try {
    return LayoutAPI::loadPlugin(std::filesystem::path(pluginPath),
                                 producerConfig)
        .release();
  } catch (...) {
  }
  return {.impl = nullptr};
}

sakls_LayoutAPI sakls_loadLayoutPluginByName(const char *pluginName,
                                             void *producerConfig) {
  try {
    return LayoutAPI::loadPlugin(std::string(pluginName), producerConfig)
        .release();
  } catch (...) {
  }
  return {.impl = nullptr};
}

SAKLS_EXTERN_C_END
