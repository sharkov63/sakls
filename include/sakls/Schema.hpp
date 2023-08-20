///
/// \file Schema.hpp
/// This file defines SAKLS Schema:
/// a language which configures SAKLS engine algorithm.
///
#ifndef SAKLS_SCHEMA_HPP
#define SAKLS_SCHEMA_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace sakls {

using LayoutID = unsigned;
using SyntaxNodeType = uint64_t;

/// SAKLS Schema: a configuration data class, which tells SAKLS engine
/// what keyboard layout to set knowing the syntax information.
///
/// Schema data class supports serialization via cereal library:
/// it is convenient to write a schema manually in, say, JSON or XML.
///
/// This class is high-level: syntax node types here are represented as strings,
/// unlike in SAKLS Engine, where they are represented by integers.
struct Schema {
  std::unordered_map<std::string, LayoutID> memorized;

  std::unordered_map<std::string, LayoutID> forced;

  std::unordered_set<std::string> ignored;

  /// Serialization method for cereal library.
  template <typename Archive> void serialize(Archive &archive);
};

/// Translates high-level schema into low-level representation for SAKLS engine.
class SchemaTranslator {
  /// Maps string syntax node types to integer syntax node types.
  std::unordered_map<std::string, SyntaxNodeType> syntaxNodeTypeMap;

  SyntaxNodeType nextSyntaxNodeType = 1;

public:
  SchemaTranslator();

  SchemaTranslator(
      const std::initializer_list<std::pair<std::string, SyntaxNodeType>>
          &list);

  [[nodiscard]] SyntaxNodeType getSyntaxNodeType(std::string_view stringType);

  void setSyntaxNodeType(std::string stringType, SyntaxNodeType intType);
};

} // namespace sakls

#endif
