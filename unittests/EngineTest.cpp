#include "EngineTest.hpp"

using namespace sakls;
using namespace sakls::unittests;

///===---------------------------------------------------------------------===//
/// EngineTest
///===---------------------------------------------------------------------===//

EngineTest::EngineTest()
    : engine(std::make_unique<Engine>(mockLayoutBackend, Schema())) {}

void EngineTest::with(Schema schema, SchemaTranslator translator) {
  engine = std::make_unique<Engine>(mockLayoutBackend, schema,
                                    std::move(translator));
}

LayoutID EngineTest::getLayout() const { return mockLayoutBackend.getLayout(); }

void EngineTest::setLayout(LayoutID layout) {
  mockLayoutBackend.setLayout(layout);
}
