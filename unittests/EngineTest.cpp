#include "EngineTest.hpp"

using namespace sakls;
using namespace sakls::unittests;

///===---------------------------------------------------------------------===//
/// EngineTest
///===---------------------------------------------------------------------===//

EngineTest::EngineTest()
    : engine(mockLayoutAPI.getAPI(), mockSyntaxAPI.getAPI(), Schema()) {}

void EngineTest::withSchema(Schema schema) {
  engine =
      Engine(mockLayoutAPI.getAPI(), mockSyntaxAPI.getAPI(), std::move(schema));
}

LayoutID EngineTest::getLayout() const { return mockLayoutAPI.getLayout(); }

void EngineTest::setLayout(LayoutID layout) { mockLayoutAPI.setLayout(layout); }

void EngineTest::push(const char *syntaxNodeType) {
  mockSyntaxAPI.push(syntaxNodeType);
}

void EngineTest::pop() { mockSyntaxAPI.pop(); }

void EngineTest::updateNewSyntaxStack(bool force) {
  engine.updateNewSyntaxStack(force);
}
