#include "sakls/Engine.hpp"

#include <cstring>

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

void Engine::saveCurrentMemorized() {
  if (!current)
    return;
  auto it = memorized.find(current->type);
  if (it == memorized.end())
    return;
  it->second = layoutBackend.getLayout();
}

void Engine::updateNewSyntaxNode(SyntaxNode newNode, bool force) {
  if (current && !force && newNode.type == current->type)
    return;
  saveCurrentMemorized();
  current = newNode;
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
  memorized.emplace(newType, layoutBackend.getDefaultLayout());
  layoutBackend.setLayout(layoutBackend.getDefaultLayout());
}

void Engine::updateNewSyntaxStack(SyntaxStackRef synStack,
                                  bool force) noexcept {
  updateNewSyntaxNode(getRelevantTop(synStack), force);
}

//===----------------------------------------------------------------------===//
// Engine C API
//===----------------------------------------------------------------------===//

extern "C" void *sakls_Engine_createWithDefaultSchema(void *layoutBackend) {
  return new Engine(*reinterpret_cast<ILayoutBackend *>(layoutBackend),
                    Schema());
}

extern "C" void sakls_Engine_delete(void *engine) {
  delete reinterpret_cast<Engine *>(engine);
}
