///
/// \file EngineTests.cpp
/// This file contains unit-tests for SAKLS engine.
///
#include "EngineTest.hpp"
#include "MockLayoutAPI.hpp"
#include "MockSyntaxAPI.hpp"
#include "doctest/doctest.h"
#include "sakls/Engine.hpp"

using namespace sakls;
using namespace sakls::unittests;

namespace {

TEST_CASE_FIXTURE(EngineTest, "Nothing") {}

TEST_CASE_FIXTURE(EngineTest, "Default is memorized") {
  CHECK(getLayout() == 0);
  push("syntaxA");
  updateNewSyntaxStack();
  setLayout(1);
  pop();
  updateNewSyntaxStack();
  CHECK(getLayout() == 0);
  push("syntaxA");
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Empty synstack top type is empty string") {
  updateNewSyntaxStack();
  setLayout(1);
  push("syntaxA");
  updateNewSyntaxStack();
  CHECK(getLayout() == 0);
  push("");
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Empty string is explicitly memorized") {
  withSchema(Schema{.memorized = {{"", 1}}});
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Forced syntax node") {
  withSchema(Schema{.forced = {{"syntaxA", 1}}});
  push("syntaxA");
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
  setLayout(0);
  updateNewSyntaxStack();
  CHECK(getLayout() == 0);
  push("syntaxB");
  updateNewSyntaxStack();
  CHECK(getLayout() == 0);
  pop();
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Ignored syntax node") {
  withSchema(Schema{.ignored = {{"ignored"}}});
  push("syntaxA");
  updateNewSyntaxStack();
  setLayout(1);
  push("ignored");
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
  push("syntaxB");
  updateNewSyntaxStack();
  CHECK(getLayout() == 0);
  pop();
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
  pop();
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
  pop();
  updateNewSyntaxStack();
  CHECK(getLayout() == 0);
}

TEST_CASE_FIXTURE(EngineTest, "No force same forced syntax node") {
  withSchema(Schema{.forced = {{"forced", 0}}});
  push("forced");
  updateNewSyntaxStack();
  setLayout(1);
  push("forced");
  updateNewSyntaxStack();
  CHECK(getLayout() == 1);
}

TEST_CASE_FIXTURE(EngineTest, "Force same forced syntax node") {
  withSchema(Schema{.forced = {{"forced", 0}}});
  push("forced");
  updateNewSyntaxStack();
  setLayout(1);
  push("forced");
  updateNewSyntaxStack(true);
  CHECK(getLayout() == 0);
}

} // namespace
