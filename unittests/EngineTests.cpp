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
  CHECK(layoutBackend.getLayout() == 0);
  engine->setNewSyntaxStack({{1}});
  layoutBackend.setLayout(1);
  engine->setNewSyntaxStack({});
  CHECK(layoutBackend.getLayout() == 0);
  engine->setNewSyntaxStack({{1}});
  CHECK(layoutBackend.getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Empty synstack top type is 0") {
  engine->setNewSyntaxStack({});
  layoutBackend.setLayout(1);
  engine->setNewSyntaxStack({{1}});
  CHECK(layoutBackend.getLayout() == 0);
  engine->setNewSyntaxStack({{1}, {0}});
  CHECK(layoutBackend.getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Empty string is explicitly memorized") {
  engine->setSchemaTranslator(SchemaTranslator{{"", 0}});
  engine->useSchema(Schema{.memorized = {{"", 1}}});
  engine->setNewSyntaxStack({});
  CHECK(layoutBackend.getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Forced syntax node") {
  engine->useSchema(Schema{.forced = {{"syntaxA", 1}}});
  engine->setNewSyntaxStack({{1}});
  CHECK(layoutBackend.getLayout() == 1);
  layoutBackend.setLayout(0);
  engine->setNewSyntaxStack({{1}});
  CHECK(layoutBackend.getLayout() == 0);
  engine->setNewSyntaxStack({{1}, {2}});
  CHECK(layoutBackend.getLayout() == 0);
  engine->setNewSyntaxStack({{1}});
  CHECK(layoutBackend.getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Ignored syntax node") {
  engine->setSchemaTranslator(SchemaTranslator{{"ignored", 10}});
  engine->useSchema(Schema{.ignored = {{"ignored"}}});
  engine->setNewSyntaxStack({{1}});
  layoutBackend.setLayout(1);
  engine->setNewSyntaxStack({{1}, {10}});
  CHECK(layoutBackend.getLayout() == 1);
  engine->setNewSyntaxStack({{1}, {10}, {2}});
  CHECK(layoutBackend.getLayout() == 0);
  engine->setNewSyntaxStack({{1}, {10}});
  CHECK(layoutBackend.getLayout() == 1);
  engine->setNewSyntaxStack({{1}});
  CHECK(layoutBackend.getLayout() == 1);
  engine->setNewSyntaxStack({});
  CHECK(layoutBackend.getLayout() == 0);
}

TEST_CASE_FIXTURE(EngineTest, "No force same forced syntax node") {
  engine->useSchema(Schema{.forced = {{"forced", 0}}});
  engine->setNewSyntaxStack({{1}});
  layoutBackend.setLayout(1);
  engine->setNewSyntaxStack({{1}, {1}});
  CHECK(layoutBackend.getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Force same forced syntax node") {
  engine->useSchema(Schema{.forced = {{{1}, 0}}});
  engine->setNewSyntaxStack({{1}});
  layoutBackend.setLayout(1);
  engine->setNewSyntaxStack({{1}, {1}}, true);
  CHECK(layoutBackend.getLayout() == 0);
}

TEST_CASE_FIXTURE(EngineTest, "Reset") {
  engine->setNewSyntaxStack({{1}});
  CHECK(layoutBackend.getLayout() == 0);
  layoutBackend.setLayout(1);
  engine->reset();
  layoutBackend.setLayout(0);
  engine->setNewSyntaxStack({{1}});
  CHECK(layoutBackend.getLayout() == 1);
}

} // namespace
