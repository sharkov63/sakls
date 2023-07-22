#ifndef SAKLS_UNITTESTS_ENGINE_TEST_HPP
#define SAKLS_UNITTESTS_ENGINE_TEST_HPP

#include "MockLayoutAPI.hpp"
#include "MockSyntaxAPI.hpp"
#include "sakls/Engine.hpp"

namespace sakls::unittests {

/// A test fixture class for unit-testing SAKLS engine.
class EngineTest {
  MockLayoutAPI mockLayoutAPI;
  MockSyntaxAPI mockSyntaxAPI;
  Engine engine;

protected:
  EngineTest();

  /// Initialize SAKLS engine with given schema.
  void withSchema(Schema schema);

  /// Get current keyboard layout from mock layout API.
  LayoutID getLayout() const;

  /// Set current keyboard layout using mock layout API.
  void setLayout(LayoutID layout);

  /// Push a syntax node with given type on the syntax stack
  /// using mock syntax API.
  void push(const char *syntaxNodeType);

  /// Pop syntax node from the syntax stack using mock syntax API.
  void pop();

  /// Call updateNewSyntaxStack in the engine.
  void updateNewSyntaxStack(bool force = false);
};

} // namespace sakls::unittests

#endif
