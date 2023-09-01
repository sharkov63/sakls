///
/// \file Schema.h
///
#ifndef SAKLS_SCHEMA_H
#define SAKLS_SCHEMA_H

#include "sakls-c/ExternC.h"

#include "stddef.h"
#include "stdint.h"

SAKLS_EXTERN_C_BEGIN

typedef unsigned sakls_LayoutID;
typedef const char *sakls_StringSyntaxNodeType;

void *sakls_Schema_create();

void sakls_Schema_setMemorized(void *schema, sakls_StringSyntaxNodeType type,
                               sakls_LayoutID defaultLayout);

void sakls_Schema_setForced(void *schema, sakls_StringSyntaxNodeType type,
                            sakls_LayoutID layout);

void sakls_Schema_setIgnored(void *schema, sakls_StringSyntaxNodeType type);

void sakls_Schema_delete(void *schema);

struct sakls_SchemaTranslator {
  struct {
    sakls_StringSyntaxNodeType stringType;
    uint64_t intType;
  } *map;
  size_t size;
};

SAKLS_EXTERN_C_END

#endif
