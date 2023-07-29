#include "EngineTest.hpp"

using namespace sakls;
using namespace sakls::unittests;

///===---------------------------------------------------------------------===//
/// EngineTest
///===---------------------------------------------------------------------===//

EngineTest::EngineTest() : engine(mockLayoutAPI.getAPI(), Schema()) {}

void EngineTest::withSchema(Schema schema) {
  engine = Engine(mockLayoutAPI.getAPI(), std::move(schema));
}

LayoutID EngineTest::getLayout() const { return mockLayoutAPI.getLayout(); }

void EngineTest::setLayout(LayoutID layout) { mockLayoutAPI.setLayout(layout); }

void EngineTest::updateNewSyntaxStack(SyntaxStackRef synStack, bool force) {
  engine.updateNewSyntaxStack(synStack, force);
}
