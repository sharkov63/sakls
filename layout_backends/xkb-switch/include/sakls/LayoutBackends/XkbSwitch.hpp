///
/// \file
/// This file provides a SAKLS layout backend for UNIX with X server
/// based on xkb-switch library.
///
#ifndef SAKLS_LAYOUT_BACKENDS_XKB_SWITCH_HPP
#define SAKLS_LAYOUT_BACKENDS_XKB_SWITCH_HPP

#include <memory>

namespace sakls {

class ILayoutBackend;

namespace xkbswitch {

/// \brief Create a xkb-switch layout backend.
///
/// This is one of the "real" SAKLS layout backends: it actually switches the
/// system keyboard layout using xkb-switch library.
/// xkb-switch works on UNIX systems with X server.
///
/// \param verbose Log level for xkb-switch library. Set to 2
/// to get xkb-switch to print messages to stderr.
/// \return Non-null pointer to the created backend.
/// \throws LayoutBackendError on construction failure.
std::unique_ptr<ILayoutBackend> createLayoutBackend(size_t verbose = 0);

} // namespace xkbswitch

} // namespace sakls

#endif
