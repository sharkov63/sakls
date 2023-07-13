///
/// \file LayoutAPI.h
/// This file defines the Layout API.
///
#ifndef SAKLS_LAYOUT_API_H
#define SAKLS_LAYOUT_API_H

#ifdef __cplusplus
extern "C" {
#endif

/// Identifies Layout API version.
///
/// Upon making any ABI-breaking changes in Layout API,
/// this number has to be incremented.
#define SAKLS_LAYOUT_API_VERSION 1

/// Identifier of a keyboard layout within Layout API.
///
/// Negative values mean an invalid layout (or an error).
typedef int sakls_LayoutID;

struct sakls_LayoutDescription;

/// Value of \p layoutListLen field of sakls_LayoutAPI struct,
/// which indicates that layout list is not available.
#define SAKLS_UNAVAILABLE_LAYOUT_LIST (-1)

/// Layout API: an interface providing getting & setting
/// current keyboard layout.
///
/// Layout API is agnostic of the underlying implementation, which actually
/// handles layout switching. Its possible implementations are:
///  - Implementations which call an external, platform-dependent library to
///  switch current system keyboard layout. These libraries, for example, are
///  xkb-switch (and it's derivatives like xkb-switch-win); im-select; etc.
///  These implementations are often produced by Layout Plugins (see
///  LayoutPlugin.h for more details).
///  - Implementations which switch an input method inside an application.
///  For example, switching 'iminsert' option in Vim between 0 and 1.
///  These implementations are useful when it's not possible to use a "real"
///  implementation switching system keyboard layout.
///  - Mock implementation which operates on a local variable. Useful for
///  unit-testing.
///
/// The mandatory part of the interface is getLayout and setLayout methods
/// as well as defaultLayout. Optionally, an implementation can provide
/// the list of all available layouts with their corresponding unique names.
/// This list is necessary for writing a human-readable sakls schema.
/// It is assumed that this list never changes during the whole usage of
/// Layout API.
struct sakls_LayoutAPI {
  /// An opaque pointer to the implementation of Layout API,
  /// which is passed to every method.
  ///
  /// If it is NULL, then the Layout API is invalid. For example, an error
  /// happened while producing the implementation.
  void *const impl;

  /// Default keyboard layout ID. Must be non-negative.
  const sakls_LayoutID defaultLayout;

  /// Get current keyboard layout.
  ///
  /// \param impl Pointer to the implementation of Layout API.
  /// \return The current keyboard layout ID or a negative value
  /// in case of any error.
  sakls_LayoutID (*getLayout)(void *impl);

  /// Set current keyboard layout.
  ///
  /// \param impl   Pointer to the implementation of Layout API.
  /// \param layout ID of the keyboard layout to set to.
  /// \return zero on success; non-zero value on error.
  int (*setLayout)(void *impl, sakls_LayoutID layout);

  /// Destroy the implementation of layout API, free all the resources it owns.
  ///
  /// \param impl Pointer to the implementation of Layout API.
  void (*destroy)(void *impl);

  /// The length of the layout list.
  ///
  /// The value of SAKLS_UNAVAILABLE_LAYOUT_LIST means that the layout list is
  /// not available.
  const int layoutListLen;

  /// The layout list: an optional list which specifies all available keyboard
  /// layouts.
  ///
  /// It's an array indexed with layout IDs. It's length is layoutListLen.
  /// If layoutListLen is equal to SAKLS_UNAVAILABLE_LAYOUT_LIST, then the
  /// layout list is not available.
  const struct sakls_LayoutDescription *const layoutList;
};

/// Describes a keyboard layout.
struct sakls_LayoutDescription {
  /// The name of this keyboard layout. Must be unique among all other layouts
  /// in the corresponding Layout API.
  const char *name;
};

#ifdef __cplusplus
}
#endif

#endif
