///
/// \file Engine.cpp
/// Implementation of SAKLS Engine and it's C API.
///
#include "sakls/Engine.hpp"

#include <cassert>

#include "spdlog/fmt/std.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace sakls;

//===---------------------------------------------------------------------===//
// Engine
//===---------------------------------------------------------------------===//

Engine::Engine(ILayoutBackend &layoutBackend, const Schema &schema,
               SchemaTranslator translator) noexcept
    : layoutBackend(layoutBackend), translator(std::move(translator)) {
  configure(schema);
}

void Engine::keepUp() {
  if (!node)
    return;
  auto it = memorized.find(node->type);
  if (it == memorized.end())
    return;
  it->second = layoutBackend.getLayout();
  if (logger)
    logger->trace("keepUp memorized node={} to layout={}", node->type,
                  it->second);
}

void Engine::setLayout(LayoutID layout) {
  layoutBackend.setLayout(layout);
  if (logger)
    logger->trace("setLayout {}", layout);
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

void Engine::reset() {
  keepUp();
  node.reset();
  if (logger)
    logger->trace("reset");
}

void Engine::setNewSyntaxNode(SyntaxNode newNode, bool force) {
  if (logger)
    logger->trace("setNewSyntaxNode: newNode={}, force={}, currentLayout = {}",
                  newNode.type, force, layoutBackend.getLayout());
  if (node && !force && newNode.type == node->type) {
    if (logger)
      logger->trace("setNewSyntaxNode: force=false and same node type {}",
                    node->type);
    return;
  }
  keepUp();
  node = newNode;
  SyntaxNodeType newType = newNode.type;
  if (auto forcedIt = forced.find(newType); forcedIt != forced.end()) {
    setLayout(forcedIt->second);
    return;
  }
  if (auto memorizedIt = memorized.find(newType);
      memorizedIt != memorized.end()) {
    setLayout(memorizedIt->second);
    return;
  }
  assert(!forced.count(newNode.type));
  memorized.emplace(newType, layoutBackend.getDefaultLayout());
  setLayout(layoutBackend.getDefaultLayout());
}

void Engine::setNewSyntaxStack(SyntaxStackRef synStack, bool force) {
  setNewSyntaxNode(getRelevantTop(synStack), force);
}

void Engine::setLogging(std::filesystem::path logFile) {
  logger = spdlog::basic_logger_mt("SAKLS Engine", std::move(logFile));
  logger->set_level(spdlog::level::trace);
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
                                             struct sakls_SyntaxNode newNode,
                                             int force) {
  try {
    ENGINE(opaqueEngine)->setNewSyntaxNode(newNode, force);
    return 0;
  } catch (...) {
  }
  return -1;
}

extern "C" int sakls_Engine_setNewSyntaxStack(
    void *opaqueEngine, struct sakls_SyntaxStackRef synStack, int force) {
  try {
    ENGINE(opaqueEngine)->setNewSyntaxStack(synStack, force);
    return 0;
  } catch (...) {
  }
  return -1;
}

extern "C" int sakls_Engine_setLogging(void *opaqueEngine,
                                       const char *logFilePath) {
  try {
    ENGINE(opaqueEngine)->setLogging(logFilePath);
    return 0;
  } catch (...) {
  }
  return -1;
}

extern "C" void sakls_Engine_delete(void *opaqueEngine) {
  delete ENGINE(opaqueEngine);
}

#undef ENGINE
