#include "sakls/SchemaSerialization.hpp"
#include "cereal/archives/json.hpp"
#include "doctest/doctest.h"

using namespace sakls;

namespace {

TEST_CASE("Schema JSON Serialization") {
  Schema schema{.memorized = {{"syntaxA", 0}},
                .forced = {{"syntaxB", 1}},
                .ignored = {"syntaxC"}};
  std::stringstream stream;
  {
    cereal::JSONOutputArchive archive(stream);
    schema.serialize(archive);
  }
  CHECK(stream.str() == R"json({
    "memorized": {
        "syntaxA": 0
    },
    "forced": {
        "syntaxB": 1
    },
    "ignored": [
        "syntaxC"
    ]
})json");
}

TEST_CASE("Schema JSON Deserialization") {
  std::string json = R"json({
    "memorized": {
        "syntaxA": 0,
        "syntaxB": 1,
        "syntaxC": 2,
        "syntaxD": 0
    },
    "forced": {
        "syntaxE": 0,
        "syntaxF": 2
    },
    "ignored": [
        "syntaxG",
        "syntaxH",
        "syntaxI"
    ]
})json";
  std::istringstream stream(json);
  Schema schema;
  {
    cereal::JSONInputArchive archive(stream);
    schema.serialize(archive);
  }
  CHECK_EQ(schema.memorized,
           std::unordered_map<std::string, sakls::LayoutID>{
               {"syntaxA", 0}, {"syntaxB", 1}, {"syntaxC", 2}, {"syntaxD", 0}});
  CHECK_EQ(schema.forced, std::unordered_map<std::string, sakls::LayoutID>{
                              {"syntaxE", 0}, {"syntaxF", 2}});
  CHECK_EQ(schema.ignored,
           std::unordered_set<std::string>{"syntaxG", "syntaxH", "syntaxI"});
}

} // namespace
