///
/// \file Engine.h
/// SAKLS Engine C API.
///
/// Delegates to Engine C++ API.
///
#ifndef SAKLS_C_ENGINE_H
#define SAKLS_C_ENGINE_H

#include "sakls-c/ExternC.h"
#include "sakls-c/Syntax.h"

SAKLS_EXTERN_C_BEGIN

/// \deprecated Temporary, while schema is not supported.
void *sakls_Engine_createWithDefaultSchema(void *layoutBackend);

/// \brief Set the Engine state to inactive.
///
/// \param engine Pointer to the SAKLS engine.
/// \return 0 on success; non-zero value on error.
int sakls_Engine_reset(void *engine);

/// \brief Set currently observed syntax node.
///
/// \pre newNode must not be an ignored syntax node.
///
/// This is a cheap way to update the Engine; it allows to directly set the
/// current syntax node without passing the whole syntax stack. However, the
/// user must guarantee that the new node is not an ignored syntax node.
///
/// \param engine Pointer to the SAKLS engine.
/// \param newNode New observed syntax node.
/// \param force Change the layout even if the type of the current syntax node
/// hasn't been changed.
/// \return 0 on success; non-zero value on error.
int sakls_Engine_setNewSyntaxNode(void *engine, sakls_SyntaxNode newNode,
                                  int force);

/// \brief Replace the currently observed syntax stack with a new one.
///
/// This is the most flexible way to update an Engine, but it is also the
/// most expensive one: in the worst case it requires to traverse the whole
/// syntax stack.
///
/// \param engine Pointer to the SAKLS engine.
/// \param synStack The new syntax stack.
/// \param force Change the layout even if the type of the current syntax node
/// hasn't been changed.
/// \return 0 on success; non-zero value on error.
int sakls_Engine_setNewSyntaxStack(void *engine, sakls_SyntaxStackRef synStack,
                                   int force);

/// \brief Destroy a SAKLS engine.
///
/// \param engine Pointer to SAKLS engine to destroy.
void sakls_Engine_delete(void *engine);

SAKLS_EXTERN_C_END

#endif
