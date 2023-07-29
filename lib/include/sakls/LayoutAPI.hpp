///
/// \file LayoutAPI.hpp
/// This file contains definitions of C++ SAKLS Layout API.
///
#ifndef SAKLS_LAYOUT_API_HPP
#define SAKLS_LAYOUT_API_HPP

#include "sakls/CAPI/LayoutAPI.h"

#include <filesystem>
#include <memory>
#include <stdexcept>

namespace sakls {

/// Identifier of a keyboard layout within a layout API implementation.
using LayoutID = ::sakls_LayoutID;

/// Describes a keyboard layout.
using LayoutDescription = ::sakls_LayoutDescription;

/// An exception related to layout API
/// (happened during a call to layout API or during it's construction/loading).
class LayoutAPIException : public std::runtime_error {
public:
  LayoutAPIException(std::string explanation);
};

/// A non-owning reference to a layout API implementation.
/// (It does not call \p destroy layout API method upon its destruction.)
class LayoutAPIRef {
protected:
  /// Underlying C layout API.
  sakls_LayoutAPI cAPI;

public:
  /// Create uninitialized layout API reference.
  LayoutAPIRef();

  /// Obtain reference of C layout API.
  explicit LayoutAPIRef(sakls_LayoutAPI cAPI);

  /// \return true if the object references a valid layout API implementation.
  bool initialized() const;

  /// Get current keyboard layout.
  ///
  /// \return ID of the current keyboard layout.
  /// \throws LayoutAPIException
  LayoutID getLayout() const;

  /// Set current keyboard layout.
  ///
  /// \param layout ID of the layout to set to.
  /// \throws LayoutAPIException
  void setLayout(LayoutID layout);

  /// Get default keyboard layout.
  LayoutID getDefaultLayout() const;

  /// Destroy the layout API implementation (if it's initialized).
  void destroy();
};

/// A C++ layout API implementation object, which owns all the implementation
/// (\p destroy method of layout API is called in the destructor).
///
/// Inherits LayoutAPIRef only to expose useful public methods.
class LayoutAPI final : public LayoutAPIRef {
public:
  /// Obtain ownership of C layout API struct.
  explicit LayoutAPI(sakls_LayoutAPI cAPI);

  LayoutAPI(const LayoutAPI &other) = delete;
  LayoutAPI &operator=(const LayoutAPI &other) = delete;

  /// Release ownership, return C layout API.
  sakls_LayoutAPI release();

  /// Destroy layout API.
  ~LayoutAPI();

  /// Load a layout plugin; produce and obtain a layout API implementation.
  /// (The implementation will also own the connection to the plugin.)
  ///
  /// \param lib Full path to the layout plugin library (including all
  /// decorations and the file extension). May be absolute or relative to the
  /// current working directory.
  /// \param producerConfig An opaque pointer to plugin-defined configuration
  /// data.
  /// \return Valid layout API implementation.
  /// \throws LayoutAPIException
  static LayoutAPI loadPlugin(const std::filesystem::path &lib,
                              void *producerConfig);
  /// \param dir Path to the directory containing the layout plugin.
  /// \param libName Name of the layout plugin library (without decorations and
  /// file extensions; e.g. 'myplug' and not 'libmyplug.so' for Unix).
  /// \throws LayoutAPIException
  static LayoutAPI loadPlugin(const std::filesystem::path &dir,
                              const std::string &libName, void *producerConfig);
  /// Load a system-installed layout plugin library.
  ///
  /// \param libName Name of the layout plugin library (without decorations and
  /// file extensions; e.g. 'myplug' and not 'libmyplug.so' for Unix).
  /// \throws LayoutAPIException
  static LayoutAPI loadPlugin(const std::string &libName, void *producerConfig);
};

} // namespace sakls

#endif
