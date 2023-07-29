///
/// \file Schema.hpp
/// This file defines SAKLS Schema: a language which configures SAKLS engine
/// algorithm.
///
#ifndef SAKLS_SCHEMA_HPP
#define SAKLS_SCHEMA_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace sakls {

using LayoutID = unsigned;

/// SAKLS Schema: a configuration data class which tell SAKLS engine
/// what keyboard layout to set knowing the syntax information.
///
/// Schema data class supports serialization via cereal library:
/// it is convenient to write a schema manually in, say, JSON or XML.
struct Schema {
  std::unordered_map<std::string, LayoutID> memorized;

  std::unordered_map<std::string, LayoutID> forced;

  std::unordered_set<std::string> ignored;

  /// Serialization method for cereal library.
  template <typename Archive> void serialize(Archive &archive);
};

} // namespace sakls

#endif
