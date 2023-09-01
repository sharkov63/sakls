///
/// \file Schema.h
///
#ifndef SAKLS_SCHEMA_H
#define SAKLS_SCHEMA_H

#include "sakls-c/ExternC.h"

#include "stddef.h"
#include "stdint.h"

SAKLS_EXTERN_C_BEGIN

struct sakls_SchemaEntry {
  const char *syntaxNodeType;
  unsigned layoutID;
};

struct sakls_Schema {
  sakls_SchemaEntry *memorized;
  size_t memorizedSize;
  sakls_SchemaEntry *forced;
  size_t forcedSize;
  const char **ignored;
  size_t ignoredSize;
};

struct sakls_SchemaTranslator {
  struct {
    const char *stringType;
    uint64_t intType;
  } *map;
  size_t size;
};

SAKLS_EXTERN_C_END

#endif
