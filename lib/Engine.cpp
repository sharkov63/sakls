///
/// \file Engine.cpp
/// Implementation of SAKLS Engine and it's C API.
///
#include "sakls/Engine.hpp"

#include <cassert>

using namespace sakls;

//===---------------------------------------------------------------------===//
// Engine
//===---------------------------------------------------------------------===//

Engine::Engine(ILayoutBackend &layoutBackend, const Schema &schema,
               SchemaTranslator translator) noexcept
    : layoutBackend(layoutBackend), translator(std::move(translator)) {
  configure(schema);
}

void Engine::configure(const Schema &schema) {
  for (const auto &[stringType, layout] : schema.memorized) {
    SyntaxNodeType type = translator.getSyntaxNodeType(stringType);
    memorized[type] = layout;
  }
  for (const auto &[stringType, layout] : schema.forced) {
    SyntaxNodeType type = translator.getSyntaxNodeType(stringType);
    forced[type] = layout;
  }
  for (const std::string &stringType : schema.ignored) {
    SyntaxNodeType type = translator.getSyntaxNodeType(stringType);
    ignored.insert(type);
  }
}

SyntaxNode Engine::getRelevantTop(SyntaxStackRef synStack) const {
  for (auto rIt = synStack.rbegin(); rIt != synStack.rend(); ++rIt)
    if (!ignored.count(rIt->type))
      return *rIt;
  return SyntaxNode();
}

void Engine::keepUp() {
  if (!node)
    return;
  auto it = memorized.find(node->type);
  if (it != memorized.end())
    it->second = layoutBackend.getLayout();
}

void Engine::reset() {
  keepUp();
  node.reset();
}

void Engine::setNewSyntaxNode(SyntaxNode newNode, bool force) {
  if (node && !force && newNode.type == node->type)
    return;
  keepUp();
  node = newNode;
  SyntaxNodeType newType = newNode.type;
  if (auto forcedIt = forced.find(newType); forcedIt != forced.end()) {
    layoutBackend.setLayout(forcedIt->second);
    return;
  }
  if (auto memorizedIt = memorized.find(newType);
      memorizedIt != memorized.end()) {
    layoutBackend.setLayout(memorizedIt->second);
    return;
  }
  assert(!forced.count(newNode.type));
  memorized.emplace(newType, layoutBackend.getDefaultLayout());
  layoutBackend.setLayout(layoutBackend.getDefaultLayout());
}

void Engine::setNewSyntaxStack(SyntaxStackRef synStack, bool force) {
  setNewSyntaxNode(getRelevantTop(synStack), force);
}

//===----------------------------------------------------------------------===//
// Engine C API
//===----------------------------------------------------------------------===//

#define ENGINE(opaqueEngine) reinterpret_cast<Engine *>(opaqueEngine)

extern "C" void *sakls_Engine_createWithDefaultSchema(void *layoutBackend) {
  return new Engine(*reinterpret_cast<ILayoutBackend *>(layoutBackend),
                    Schema());
}

extern "C" int sakls_Engine_reset(void *opaqueEngine) {
  try {
    ENGINE(opaqueEngine)->reset();
    return 0;
  } catch (...) {
  }
  return -1;
}

extern "C" int sakls_Engine_setNewSyntaxNode(void *opaqueEngine,
                                             sakls_SyntaxNode newNode,
                                             int force) {
  try {
    ENGINE(opaqueEngine)->setNewSyntaxNode(newNode, force);
  } catch (...) {
  }
  return -1;
}

extern "C" int sakls_Engine_setNewSyntaxStack(void *opaqueEngine,
                                              sakls_SyntaxStackRef synStack,
                                              int force) {
  try {
    ENGINE(opaqueEngine)->setNewSyntaxStack(synStack, force);
  } catch (...) {
  }
  return -1;
}

extern "C" void sakls_Engine_delete(void *opaqueEngine) {
  delete ENGINE(opaqueEngine);
}

#undef ENGINE
