///
/// \file LayoutAPI.h
/// This file defines the C SAKLS Layout API.
///
#ifndef SAKLS_LAYOUT_API_H
#define SAKLS_LAYOUT_API_H

#include "sakls/CAPI/ExternC.h"

SAKLS_EXTERN_C_BEGIN

/// Identifies Layout API version.
///
/// Upon making any ABI compatibility breaking changes in Layout API,
/// this number has to be incremented.
///
/// TODO: upon release start this with 1
#define SAKLS_LAYOUT_API_VERSION 0

/// Identifier of a keyboard layout within Layout API.
typedef unsigned sakls_LayoutID;

struct sakls_LayoutDescription;

/// Layout API: interface providing getting & setting current keyboard layout.
///
/// Layout API is agnostic of the underlying implementation, which actually
/// handles layout switching. Its possible implementations are:
///  - Implementations which call an external, platform-dependent library to
///  switch current system keyboard layout. These libraries, for example, are
///  xkb-switch (and it's derivatives like xkb-switch-win); im-select; etc.
///  These implementations are often produced by Layout Plugins
///  (see sakls/LayoutPlugin.h for more details).
///  - Implementations which switch an input method inside an application.
///  For example, switching 'iminsert' option in Vim between 0 and 1.
///  These implementations are useful when it's not possible to use a "real"
///  implementation switching system keyboard layout.
///  - Mock implementation which operates on a local variable. Useful for
///  unit-testing. See "unittests/MockLayoutAPI.hpp".
///
/// The mandatory part of the interface is getLayout and setLayout methods
/// as well as defaultLayout. Optionally, an implementation can provide
/// the list of all available layouts with their corresponding unique names.
/// This list is necessary for writing a human-readable SAKLS schema.
/// It is assumed that this list never changes during the whole usage of
/// Layout API.
struct sakls_LayoutAPI {
  /// An opaque pointer to the implementation of Layout API,
  /// which is passed to every method.
  ///
  /// If it is null, then the Layout API is invalid. For example, an error
  /// happened while producing the implementation.
  void *impl;

  /// Default keyboard layout ID.
  sakls_LayoutID defaultLayout;

  /// Get current keyboard layout.
  ///
  /// \param impl Pointer to the implementation of Layout API.
  /// \param[out] layout Place to put the current keyboard layout ID.
  /// \return zero on success; non-zero value on error.
  int (*getLayout)(void *impl, sakls_LayoutID *layout);

  /// Set current keyboard layout.
  ///
  /// It is not required that the function sets the layout immediately:
  /// it is sufficient to send a request to set the layout.
  ///
  /// \param impl Pointer to the implementation of Layout API.
  /// \param layout ID of the keyboard layout to set to.
  /// \return zero on success; non-zero value on error.
  int (*setLayout)(void *impl, sakls_LayoutID layout);

  /// Destroy the implementation of layout API, free all the resources it owns.
  ///
  /// \param impl Pointer to the implementation of Layout API.
  void (*destroy)(void *impl);

  /// The length of the layout list.
  int layoutListLen;

  /// The layout list: an optional list which specifies all available keyboard
  /// layouts.
  ///
  /// It's an array indexed with layout IDs. It's length is layoutListLen.
  ///
  /// If this pointer is null, then the layout list is not available.
  const struct sakls_LayoutDescription *layoutList;
};

/// Describes a keyboard layout.
struct sakls_LayoutDescription {
  /// The name of this keyboard layout. Must be unique among all other layouts
  /// in the corresponding Layout API.
  const char *name;
};

SAKLS_EXTERN_C_END

#endif
