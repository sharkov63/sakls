///
/// \file LayoutAPI.hpp
/// This file contains useful C++ wrappers
/// and convenience functions for the C SAKLS Layout API.
///
#ifndef SAKLS_LAYOUT_API_HPP
#define SAKLS_LAYOUT_API_HPP

#include "sakls/LayoutAPI.h"

#include <stdexcept>

namespace sakls {

/// Identifier of a keyboard layout within Layout API.
using LayoutID = ::sakls_LayoutID;

/// Describes a keyboard layout.
using LayoutDescription = ::sakls_LayoutDescription;

/// An exception which happened during a call to Layout API.
class LayoutAPIException : public std::runtime_error {
public:
  LayoutAPIException(std::string explanation);
};

/// A convenience C++ wrapper around sakls_LayoutAPI.
///
/// This wrapper does not own the implementation of Layout API:
/// when it is destroyed, it does not call destroy method of Layout API.
class LayoutAPIRef {
  /// Underlying C Layout API structure.
  sakls_LayoutAPI cAPI;

public:
  /// Convert from C API.
  explicit LayoutAPIRef(sakls_LayoutAPI cAPI);

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

  /// Destroy Layout API.
  void destroy();
};

} // namespace sakls

#endif
