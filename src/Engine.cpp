#include "sakls/Engine.hpp"

#include <cstring>

using namespace sakls;

///===---------------------------------------------------------------------===//
/// Engine
///===---------------------------------------------------------------------===//

Engine::Engine(LayoutAPIRef layoutAPI, SyntaxAPIRef syntaxAPI, Schema schema)
    : layoutAPI(layoutAPI), syntaxAPI(syntaxAPI), schema(std::move(schema)) {}

SyntaxNode Engine::getRelevantTop() const {
  SyntaxStackRef syntaxStack = syntaxAPI.getSyntaxStack();
  for (long index = (long)syntaxStack.size - 1; index >= 0; --index) {
    SyntaxNode node = syntaxStack.addr[index];
    if (!schema.ignored.count(node.getType()))
      return node;
  }
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

void Engine::updateNewSyntaxStack(bool force) {
  updateNewSyntaxNode(getRelevantTop(), force);
}
