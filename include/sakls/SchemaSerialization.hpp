///
/// \file SchemaSerialization.hpp
///
#ifndef SAKLS_SCHEMA_SERIALIZATION_HPP
#define SAKLS_SCHEMA_SERIALIZATION_HPP

#include "cereal/cereal.hpp"
#include "cereal/details/traits.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/unordered_set.hpp"
#include "sakls/Schema.hpp"

namespace cereal {

template <
    typename Archive,
    traits::EnableIf<traits::is_text_archive<Archive>::value> = traits::sfinae>
void save(Archive &archive,
          const std::unordered_map<std::string, sakls::LayoutID> &map) {
  for (const auto &[key, value] : map)
    archive(cereal::make_nvp(key, value));
}

template <
    typename Archive,
    traits::EnableIf<traits::is_text_archive<Archive>::value> = traits::sfinae>
void load(Archive &archive,
          std::unordered_map<std::string, sakls::LayoutID> &map) {
  map.clear();
  while (true) {
    const auto namePtr = archive.getNodeName();

    if (!namePtr)
      break;

    std::string key = namePtr;
    sakls::LayoutID value;
    archive(value);
    map[key] = value;
  }
}

} // namespace cereal

namespace sakls {

template <typename Archive> void Schema::serialize(Archive &archive) {
  archive(CEREAL_NVP(memorized), CEREAL_NVP(forced), CEREAL_NVP(ignored));
}

} // namespace sakls

#endif
