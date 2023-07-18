///
/// \file LayoutAPI.hpp
/// This file contains useful C++ wrappers
/// and convenience functions for the C SAKLS Layout API.
///
#ifndef SAKLS_LAYOUT_API_HPP
#define SAKLS_LAYOUT_API_HPP

#include "sakls/LayoutAPI.h"

#include <exception>

namespace sakls {

/// Identifier of a keyboard layout within Layout API.
using LayoutID = ::sakls_LayoutID;

/// An exception which happened during a call to Layout API.
class LayoutAPIException : public std::exception {};

/// A convenience C++ wrapper around sakls_LayoutAPI.
///
/// This wrapper does not own the implementation of Layout API:
/// when it is destroyed, it does not call destroy method of Layout API.
class LayoutAPIRef {
  /// Underlying C Layout API structure.
  sakls_LayoutAPI cAPI;

public:
  explicit LayoutAPIRef(sakls_LayoutAPI cAPI);

  /// Get current keyboard layout.
  ///
  /// \return Non-negative valid layout ID
  /// \throws LayoutAPIException
  LayoutID getLayout() const;

  /// Set current keyboard layout.
  ///
  /// \param layout Non-negative valid layout ID
  /// \throws LayoutAPIException
  void setLayout(LayoutID layout);

  /// Destroy Layout API.
  void destroy();
};

} // namespace sakls

#endif
