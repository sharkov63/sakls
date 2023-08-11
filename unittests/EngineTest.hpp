#ifndef SAKLS_UNITTESTS_ENGINE_TEST_HPP
#define SAKLS_UNITTESTS_ENGINE_TEST_HPP

#include "MockLayoutBackend.hpp"
#include "sakls/Engine.hpp"

#include <memory>

namespace sakls::unittests {

/// A test fixture class for unit-testing SAKLS engine.
class EngineTest {
  mutable MockLayoutBackend mockLayoutBackend;
  std::unique_ptr<Engine> engine;

protected:
  EngineTest();

  /// Initialize SAKLS engine with given schema.
  void withSchema(Schema schema);

  /// Get current keyboard layout from mock layout backend.
  LayoutID getLayout() const;

  /// Set current keyboard layout using mock layout backend.
  void setLayout(LayoutID layout);

  /// Call updateNewSyntaxStack in the engine.
  void updateNewSyntaxStack(SyntaxStackRef synStack, bool force = false);
};

} // namespace sakls::unittests

#endif
