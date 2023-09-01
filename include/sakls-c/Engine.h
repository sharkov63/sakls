///
/// \file Engine.h
/// SAKLS Engine C API.
///
/// Delegates to Engine C++ API.
///
#ifndef SAKLS_C_ENGINE_H
#define SAKLS_C_ENGINE_H

#include "sakls-c/ExternC.h"
#include "sakls-c/Schema.h"
#include "sakls-c/Syntax.h"

SAKLS_EXTERN_C_BEGIN

/// \brief Create a SAKLS engine.
///
/// Created engine is inactive (see Engine state)
/// and has default schema and schema translator which are empty.
///
/// \param layoutBackend Layout backend for the engine to use.
void *sakls_Engine_create(void *layoutBackend);

/// \brief Set Schema translator of this Engine.
///
/// \param engine Pointer to the SAKLS engine.
/// \param translator Schema translator, which translates string syntax node
/// types (seen in high-level schema) into integer syntax node types
/// (used in Engine for computations).
///
/// In case when the user is also aware about the translation, and passes
/// integer syntax node types in calls to Engine API, the user must guarantee
/// that this translation is valid during the whole lifetime of the Engine.
void sakls_Engine_setSchemaTranslator(void *engine,
                                      struct sakls_SchemaTranslator translator);

/// \brief Configure Engine algorithm by a SAKLS Schema.
///
/// The passed high-level schema contains string syntax node types,
/// they are converted to integer syntax node types by Schema translator.
///
/// \param engine Pointer to the SAKLS engine.
/// \param schema High-level SAKLS schema.
void sakls_Engine_useSchema(void *engine, void *schema);

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
int sakls_Engine_setNewSyntaxNode(void *engine, struct sakls_SyntaxNode newNode,
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
int sakls_Engine_setNewSyntaxStack(void *engine,
                                   struct sakls_SyntaxStackRef synStack,
                                   int force);

/// Make SAKLS Engine log to a file at #logFilePath.
///
/// \param engine Pointer to the SAKLS engine.
/// \param logFilePath Path to the log file.
void sakls_Engine_setLogging(void *engine, const char *logFilePath);

/// \brief Destroy a SAKLS engine.
///
/// \param engine Pointer to SAKLS engine to destroy.
void sakls_Engine_delete(void *engine);

SAKLS_EXTERN_C_END

#endif
