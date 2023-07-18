///
/// \file Schema.hpp
///
#ifndef SAKLS_SCHEMA_HPP
#define SAKLS_SCHEMA_HPP

#include "sakls/LayoutAPI.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace sakls {

struct Schema {
  std::unordered_map<std::string, LayoutID> memorized;
  std::unordered_map<std::string, LayoutID> forced;
  std::unordered_set<std::string> ignored;

  LayoutAPIRef layoutAPI;
};

} // namespace sakls

#endif
