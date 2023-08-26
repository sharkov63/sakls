///
/// \file EngineTests.cpp
/// This file contains unit-tests for SAKLS engine.
///
#include "EngineTest.hpp"
#include "doctest/doctest.h"
#include "sakls/Engine.hpp"

using namespace sakls;
using namespace sakls::unittests;

namespace {

TEST_CASE_FIXTURE(EngineTest, "Nothing") {}

TEST_CASE_FIXTURE(EngineTest, "Default is memorized") {
  CHECK(getLayout() == 0);
  engine->setNewSyntaxStack({{1}});
  setLayout(1);
  engine->setNewSyntaxStack({});
  CHECK(getLayout() == 0);
  engine->setNewSyntaxStack({{1}});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Empty synstack top type is 0") {
  engine->setNewSyntaxStack({});
  setLayout(1);
  engine->setNewSyntaxStack({{1}});
  CHECK(getLayout() == 0);
  engine->setNewSyntaxStack({{1}, {0}});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Empty string is explicitly memorized") {
  with(Schema{.memorized = {{"", 1}}}, SchemaTranslator{{"", 0}});
  engine->setNewSyntaxStack({});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Forced syntax node") {
  with(Schema{.forced = {{"syntaxA", 1}}});
  engine->setNewSyntaxStack({{1}});
  CHECK(getLayout() == 1);
  setLayout(0);
  engine->setNewSyntaxStack({{1}});
  CHECK(getLayout() == 0);
  engine->setNewSyntaxStack({{1}, {2}});
  CHECK(getLayout() == 0);
  engine->setNewSyntaxStack({{1}});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Ignored syntax node") {
  with(Schema{.ignored = {{"ignored"}}}, SchemaTranslator{{"ignored", 10}});
  engine->setNewSyntaxStack({{1}});
  setLayout(1);
  engine->setNewSyntaxStack({{1}, {10}});
  CHECK(getLayout() == 1);
  engine->setNewSyntaxStack({{1}, {10}, {2}});
  CHECK(getLayout() == 0);
  engine->setNewSyntaxStack({{1}, {10}});
  CHECK(getLayout() == 1);
  engine->setNewSyntaxStack({{1}});
  CHECK(getLayout() == 1);
  engine->setNewSyntaxStack({});
  CHECK(getLayout() == 0);
}

TEST_CASE_FIXTURE(EngineTest, "No force same forced syntax node") {
  with(Schema{.forced = {{"forced", 0}}});
  engine->setNewSyntaxStack({{1}});
  setLayout(1);
  engine->setNewSyntaxStack({{1}, {1}});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Force same forced syntax node") {
  with(Schema{.forced = {{{1}, 0}}});
  engine->setNewSyntaxStack({{1}});
  setLayout(1);
  engine->setNewSyntaxStack({{1}, {1}}, true);
  CHECK(getLayout() == 0);
}

TEST_CASE_FIXTURE(EngineTest, "Reset") {
  engine->setNewSyntaxStack({{1}});
  CHECK(getLayout() == 0);
  setLayout(1);
  engine->reset();
  setLayout(0);
  engine->setNewSyntaxStack({{1}});
  CHECK(getLayout() == 1);
}

} // namespace
