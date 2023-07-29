#ifndef SAKLS_UNITTESTS_ENGINE_TEST_HPP
#define SAKLS_UNITTESTS_ENGINE_TEST_HPP

#include "MockLayoutAPI.hpp"
#include "sakls/Engine.hpp"

namespace sakls::unittests {

/// A test fixture class for unit-testing SAKLS engine.
class EngineTest {
  MockLayoutAPI mockLayoutAPI;
  Engine engine;

protected:
  EngineTest();

  /// Initialize SAKLS engine with given schema.
  void withSchema(Schema schema);

  /// Get current keyboard layout from mock layout API.
  LayoutID getLayout() const;

  /// Set current keyboard layout using mock layout API.
  void setLayout(LayoutID layout);

  /// Call updateNewSyntaxStack in the engine.
  void updateNewSyntaxStack(SyntaxStackRef synStack, bool force = false);
};

} // namespace sakls::unittests

#endif
