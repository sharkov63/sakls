#include "sakls/Schema.hpp"

using namespace sakls;

//===----------------------------------------------------------------------===//
// SchemaTranslator
//===----------------------------------------------------------------------===//

SchemaTranslator::SchemaTranslator() = default;

SchemaTranslator::SchemaTranslator(
    const std::initializer_list<std::pair<std::string, SyntaxNodeType>> &list) {
  for (const auto &[stringType, intType] : list)
    setSyntaxNodeType(stringType, intType);
}

SyntaxNodeType
SchemaTranslator::getSyntaxNodeType(std::string_view stringType) {
  auto [it, inserted] =
      syntaxNodeTypeMap.emplace(stringType, nextSyntaxNodeType);
  nextSyntaxNodeType += inserted;
  return it->second;
}

void SchemaTranslator::setSyntaxNodeType(std::string stringType,
                                         SyntaxNodeType intType) {
  syntaxNodeTypeMap.emplace(std::move(stringType), intType);
  nextSyntaxNodeType = std::max(nextSyntaxNodeType, intType + 1);
}

SchemaTranslator
SchemaTranslator::fromCTranslator(sakls_SchemaTranslator cTranslator) {
  SchemaTranslator translator;
  for (size_t i = 0; i < cTranslator.size; ++i) {
    auto entry = cTranslator.map[i];
    translator.setSyntaxNodeType(entry.stringType, entry.intType);
  }
  return translator;
}

//===----------------------------------------------------------------------===//
// Schema C API
//===----------------------------------------------------------------------===//

#define SCHEMA(opaqueSchema) (reinterpret_cast<Schema *>(opaqueSchema))

extern "C" void *sakls_Schema_create() { return new Schema(); }

extern "C" void sakls_Schema_setMemorized(void *opaqueSchema,
                                          sakls_StringSyntaxNodeType type,
                                          sakls_LayoutID defaultLayout) {
  SCHEMA(opaqueSchema)->memorized[type] = defaultLayout;
}

extern "C" void sakls_Schema_setForced(void *opaqueSchema,
                                       sakls_StringSyntaxNodeType type,
                                       sakls_LayoutID layout) {
  SCHEMA(opaqueSchema)->forced[type] = layout;
}

extern "C" void sakls_Schema_setIgnored(void *opaqueSchema,
                                        sakls_StringSyntaxNodeType type) {
  SCHEMA(opaqueSchema)->ignored.insert(type);
}

extern "C" void sakls_Schema_delete(void *opaqueSchema) {
  delete SCHEMA(opaqueSchema);
}

#undef SCHEMA
