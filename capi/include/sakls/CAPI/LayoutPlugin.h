///
/// \file LayoutPlugin.h
/// This file provides means of producing Layout API implementations
/// from external shared plugins, loaded in run-time, called "Layout Plugins".
///
#ifndef SAKLS_LAYOUT_PLUGIN_H
#define SAKLS_LAYOUT_PLUGIN_H

#include "sakls/CAPI/ExternC.h"
#include "sakls/CAPI/LayoutAPI.h"

SAKLS_EXTERN_C_BEGIN

/// Information about a loaded Layout Plugin.
///
/// A Layout Plugin is a shared plugin which can produce an implementation
/// of Layout API. Layout Plugins are loaded by SAKLS in run-time
/// using dlopen-like platform-dependent mechanisms; they are not linked
/// to SAKLS neither statically, nor dynamically.
///
/// A Layout Plugin must implement and export sakls_getLayoutPluginInfo
/// function, which fills out and returns this structure.
struct sakls_LayoutPluginInfo {
  /// The Layout API version understood by this plugin.
  /// \see SAKLS_LAYOUT_API_VERSION
  unsigned apiVersion;

  /// Human-readable plugin name.
  const char *pluginName;

  /// The version of the plugin.
  const char *pluginVersion;

  /// The callback which produces an implementation of Layout API.
  ///
  /// \param producerConfig An opaque pointer to configuration data,
  /// which format depends on the Layout Plugin.
  /// \return Implementation of Layout API. If an error happened,
  /// the \p impl field of the return value is null.
  struct sakls_LayoutAPI (*produceLayoutAPIImpl)(void *producerConfig);
};

/// The public entry point for a Layout Plugin.
///
/// Every Layout Plugin must implement and export this function.
/// When a Layout Plugin is loaded, SAKLS looks up this function
/// and calls it, getting the required Layout Plugin info. Implementation
/// example:
/// ```c
/// extern "C" sakls_LayoutPluginInfo sakls_getLayoutPluginInfo() {
///   return {
///     SAKLS_LAYOUT_API_VERSION, "MyLayoutPlugin", "1.0", [](void *) { ... }
///   };
/// }
/// ```
struct sakls_LayoutPluginInfo sakls_getLayoutPluginInfo();

/// Load a layout plugin; produce and obtain a layout API implementation.
/// The implementation will also own the connection to the plugin.
///
/// \param pluginPath Full path to the layout plugin library (including all
/// decorations and the file extension). May be absolute or relative to the
/// current working directory.
/// \param producerConfig An opaque pointer to plugin-defined configuration
/// data.
/// \return Valid layout API implementation; on error object with .impl = null.
sakls_LayoutAPI sakls_loadLayoutPluginByPath(const char *pluginPath,
                                             void *producerConfig);

/// Load a system-installed layout plugin library.
///
/// \param pluginName Name of the layout plugin library (without decorations and
/// file extensions; e.g. 'myplug' and not 'libmyplug.so' for Unix).
sakls_LayoutAPI sakls_loadLayoutPluginByName(const char *pluginName,
                                             void *producerConfig);

SAKLS_EXTERN_C_END

#endif
