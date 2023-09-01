#ifndef SAKLS_UNITTESTS_ENGINE_TEST_HPP
#define SAKLS_UNITTESTS_ENGINE_TEST_HPP

#include "MockLayoutBackend.hpp"
#include "sakls/Engine.hpp"

#include <memory>

namespace sakls::unittests {

/// A test fixture class for unit-testing SAKLS engine.
class EngineTest {
protected:
  mutable MockLayoutBackend layoutBackend;
  std::unique_ptr<Engine> engine;

  EngineTest() : engine(std::make_unique<Engine>(layoutBackend)) {}
};

} // namespace sakls::unittests

#endif
