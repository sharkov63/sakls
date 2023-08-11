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
  updateNewSyntaxStack({"syntaxA"});
  setLayout(1);
  updateNewSyntaxStack({});
  CHECK(getLayout() == 0);
  updateNewSyntaxStack({"syntaxA"});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Empty synstack top type is empty string") {
  updateNewSyntaxStack({});
  setLayout(1);
  updateNewSyntaxStack({"syntaxA"});
  CHECK(getLayout() == 0);
  updateNewSyntaxStack({"syntaxA", ""});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Empty string is explicitly memorized") {
  withSchema(Schema{.memorized = {{"", 1}}});
  updateNewSyntaxStack({});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Forced syntax node") {
  withSchema(Schema{.forced = {{"syntaxA", 1}}});
  updateNewSyntaxStack({"syntaxA"});
  CHECK(getLayout() == 1);
  setLayout(0);
  updateNewSyntaxStack({"syntaxA"});
  CHECK(getLayout() == 0);
  updateNewSyntaxStack({"syntaxA", "syntaxB"});
  CHECK(getLayout() == 0);
  updateNewSyntaxStack({"syntaxA"});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Ignored syntax node") {
  withSchema(Schema{.ignored = {{"ignored"}}});
  updateNewSyntaxStack({"syntaxA"});
  setLayout(1);
  updateNewSyntaxStack({"syntaxA", "ignored"});
  CHECK(getLayout() == 1);
  updateNewSyntaxStack({"syntaxA", "ignored", "syntaxB"});
  CHECK(getLayout() == 0);
  updateNewSyntaxStack({"syntaxA", "ignored"});
  CHECK(getLayout() == 1);
  updateNewSyntaxStack({"syntaxA"});
  CHECK(getLayout() == 1);
  updateNewSyntaxStack({});
  CHECK(getLayout() == 0);
}

TEST_CASE_FIXTURE(EngineTest, "No force same forced syntax node") {
  withSchema(Schema{.forced = {{"forced", 0}}});
  updateNewSyntaxStack({"forced"});
  setLayout(1);
  updateNewSyntaxStack({"forced", "forced"});
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Force same forced syntax node") {
  withSchema(Schema{.forced = {{"forced", 0}}});
  updateNewSyntaxStack({"forced"});
  setLayout(1);
  updateNewSyntaxStack({"forced", "forced"}, true);
  CHECK(getLayout() == 0);
}

} // namespace
