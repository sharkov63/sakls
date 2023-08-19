///
/// \file XkbSwitch.h
/// C API for xkb-switch SAKLS layout backend.
///
/// See 'sakls/XkbSwitch.hpp' for more details.
///
#ifndef SAKLS_C_LAYOUT_BACKENDS_XKB_SWITCH_H
#define SAKLS_C_LAYOUT_BACKENDS_XKB_SWITCH_H

#include "sakls-c/ExternC.h"

SAKLS_EXTERN_C_BEGIN

/// \brief Create a xkb-switch layout backend.
///
/// \param[out] layoutBackend Created layout backend.
/// \return 0 on success, non-zero value on failure.
int sakls_XkbSwitch_createLayoutBackend(void **layoutBackend);

/// \brief Delete a xkb-switch layout backend.
///
/// \param layoutBackend Layout backend to delete. Can be null.
void sakls_XkbSwitch_deleteLayoutBackend(void *layoutBackend);

SAKLS_EXTERN_C_END

#endif
