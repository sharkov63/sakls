#include "sakls/Engine.hpp"

#include <cstring>

using namespace sakls;

///===---------------------------------------------------------------------===//
/// Engine
///===---------------------------------------------------------------------===//

Engine::Engine(LayoutAPIRef layoutAPI, Schema schema)
    : layoutAPI(layoutAPI), schema(std::move(schema)) {}

SyntaxNode Engine::getRelevantTop(SyntaxStackRef synStack) const {
  for (auto rIt = synStack.rbegin(); rIt != synStack.rend(); ++rIt)
    if (!schema.ignored.count(rIt->getType()))
      return *rIt;
  return SyntaxNode();
}

void Engine::saveCurrentMemorized() {
  if (!current)
    return;
  auto it = schema.memorized.find(current->getType());
  if (it == schema.memorized.end())
    return;
  it->second = layoutAPI.getLayout();
}

void Engine::updateNewSyntaxNode(SyntaxNode newNode, bool force) {
  if (current && !force &&
      std::strcmp(newNode.getType(), current->getType()) == 0)
    return;
  saveCurrentMemorized();
  current = newNode;
  const char *newType = newNode.getType();
  if (auto forcedIt = schema.forced.find(newType);
      forcedIt != schema.forced.end()) {
    layoutAPI.setLayout(forcedIt->second);
    return;
  }
  if (auto memorizedIt = schema.memorized.find(newType);
      memorizedIt != schema.memorized.end()) {
    layoutAPI.setLayout(memorizedIt->second);
    return;
  }
  schema.memorized.emplace(newType, layoutAPI.getDefaultLayout());
  layoutAPI.setLayout(layoutAPI.getDefaultLayout());
}

void Engine::updateNewSyntaxStack(SyntaxStackRef synStack, bool force) {
  updateNewSyntaxNode(getRelevantTop(synStack), force);
}
