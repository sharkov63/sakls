///
/// \file Engine.h
/// SAKLS Engine C API.
///
#ifndef SAKLS_C_ENGINE_H
#define SAKLS_C_ENGINE_H

#include "sakls-c/ExternC.h"

SAKLS_EXTERN_C_BEGIN

/// \deprecated Temporary, while schema is not supported.
void *sakls_Engine_createWithDefaultSchema(void *layoutBackend);

/// \brief Destroy a SAKLS engine.
///
/// \param engine Pointer to SAKLS engine to destory.
void sakls_Engine_delete(void *engine);

SAKLS_EXTERN_C_END

#endif
