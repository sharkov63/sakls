#include "sakls/Schema.hpp"

using namespace sakls;

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
