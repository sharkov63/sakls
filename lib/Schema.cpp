#include "sakls/Schema.hpp"

using namespace sakls;

//===----------------------------------------------------------------------===//
// Schema
//===----------------------------------------------------------------------===//

Schema Schema::fromCSchema(sakls_Schema cSchema) {
  Schema schema;
  for (size_t i = 0; i < cSchema.memorizedSize; ++i) {
    sakls_SchemaEntry entry = cSchema.memorized[i];
    schema.memorized[entry.syntaxNodeType] = entry.layoutID;
  }
  for (size_t i = 0; i < cSchema.forcedSize; ++i) {
    sakls_SchemaEntry entry = cSchema.forced[i];
    schema.forced[entry.syntaxNodeType] = entry.layoutID;
  }
  for (size_t i = 0; i < cSchema.ignoredSize; ++i)
    schema.ignored.insert(cSchema.ignored[i]);
  return schema;
}

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
