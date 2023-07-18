///
/// \file EngineAPI.h
/// This file defines the C SAKLS Engine API:
/// an interface containing methods to SAKLS Engine.
///
/// Functions of Engine API are called upon events happening in the editor,
/// such as changing file contents or moving cursor position. They trigger
/// the SAKLS Engine to collect updated syntax information via Syntax API
/// and then correctly change the current keyboard layout (via Layout API)
/// according the established rules (via Syntax-to-Layout Schema language).
///
#ifndef SAKLS_ENGINE_API_H
#define SAKLS_ENGINE_API_H

#include "sakls/ExternC.h"
#include "sakls/LayoutAPI.h"
#include "sakls/SyntaxAPI.h"

SAKLS_EXTERN_C_BEGIN

/// Identifies Engine API version.
///
/// Upon making any ABI-breaking changes in Engine API,
/// this number has to be incremented.
///
/// FIXME: upon release start this with 1
#define SAKLS_ENGINE_API_VERSION 0

/// Build a new SAKLS Engine.
///
/// The Engine does not own passed Layout API and Syntax API,
/// these are only references. It is up to the caller to
/// own these.
///
/// \param cLayoutAPI Reference to C Layout API.
/// \param cSyntaxAPI Reference to C Syntax API.
/// \return Opaque pointer to the built SAKLS Engine,
/// or null on error.
void *sakls_engine_new(struct sakls_LayoutAPI cLayoutAPI,
                       struct sakls_SyntaxAPI cSyntaxAPI);

/// Destroy SAKLS engine; free all resources it owns.
///
/// \param engine Pointer to SAKLS Engine.
void sakls_engine_delete(void *engine);

/// Trigger a SAKLS Engine update: completely replace Syntax Stack.
///
/// \param engine Pointer to SAKLS Engine.
void sakls_engine_updateNewSyntaxStack(void *engine);

SAKLS_EXTERN_C_END

#endif
