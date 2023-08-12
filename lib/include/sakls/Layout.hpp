///
/// \file Layout.hpp
/// This file defines the C++ SAKLS layout backend interface,
/// which provides means of keyboard layout manipulation.
///
#ifndef SAKLS_LIB_LAYOUT_HPP
#define SAKLS_LIB_LAYOUT_HPP

#include <stdexcept>
#include <vector>

namespace sakls {

/// Identifier of a keyboard layout within a layout backend.
/// Layout IDs are assigned starting from 0.
using LayoutID = unsigned;

/// An error which happened in layout backend (or while it's been constructed).
class LayoutBackendError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

/// Describes a keyboard layout within a layout backend.
struct LayoutDescription {
  /// The name of this keyboard layout.
  /// Must be unique among all other layouts in this layout backend.
  std::string type;
};

/// Interface of a "layout backend": an object, which provides functions of
/// getting & setting current keyboard layout.
///
/// This interface is agnostic of the underlying implementation
/// (called "layout backend"), which actually handles layout switching.
/// Possible layout backends are:
///  - "Real" layout backends, which call an external, platform-dependent
///  library to actually switch current system keyboard layout. These libraries,
///  for example, are: xkb-switch for UNIX with X11 (and it's derivatives like
///  xkb-switch-win for Windows), im-select for Mac and Windows, etc.
///  - Layout backends, which switch an input method inside an application.
///  For example, switching 'iminsert' option in Vim between 0 and 1.
///  These backends are useful when it's impossible to use a real backend.
///  - Mock layout backend which operates on a local variable - useful
///  for unit-testing. See "unittests/MockLayoutBackend.hpp".
///
/// Note that the list of all available layouts in a layout backend
/// is assumed not to change during the lifetime of this layout backend.
class ILayoutBackend {
public:
  ILayoutBackend() = default;

  virtual ~ILayoutBackend() = default;

  /// Get default keyboard layout.
  /// Usually it is 0.
  virtual LayoutID getDefaultLayout() const noexcept = 0;

  /// Get current keyboard layout.
  ///
  /// \throws LayoutBackendError
  virtual LayoutID getLayout() const = 0;

  /// Set current keyboard layout.
  ///
  /// \throws LayoutBackendError
  virtual void setLayout(LayoutID layout) = 0;

  /// Obtain the list of all available layouts in this layout backend.
  /// The indices of this list are exactly layout IDs.
  ///
  /// This list is assumed not to change during the whole lifetime of this
  /// layout backend.
  ///
  /// \throws LayoutBackendError
  virtual std::vector<LayoutDescription> allLayouts() = 0;
};

} // namespace sakls

#endif
