///
/// \file Schema.hpp
///
#ifndef SAKLS_SCHEMA_HPP
#define SAKLS_SCHEMA_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace sakls {

using LayoutID = int;

struct Schema {
  std::unordered_map<std::string, LayoutID> memorized;
  std::unordered_map<std::string, LayoutID> forced;
  std::unordered_set<std::string> ignored;

  template <typename Archive> void serialize(Archive &archive);
};

} // namespace sakls

#endif
