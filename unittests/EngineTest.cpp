#include "EngineTest.hpp"

using namespace sakls;
using namespace sakls::unittests;

///===---------------------------------------------------------------------===//
/// EngineTest
///===---------------------------------------------------------------------===//

EngineTest::EngineTest()
    : engine(std::make_unique<Engine>(mockLayoutBackend, Schema())) {}

void EngineTest::withSchema(Schema schema) {
  engine = std::make_unique<Engine>(mockLayoutBackend, std::move(schema));
}

LayoutID EngineTest::getLayout() const { return mockLayoutBackend.getLayout(); }

void EngineTest::setLayout(LayoutID layout) {
  mockLayoutBackend.setLayout(layout);
}

void EngineTest::updateNewSyntaxStack(SyntaxStackRef synStack, bool force) {
  engine->updateNewSyntaxStack(synStack, force);
}
