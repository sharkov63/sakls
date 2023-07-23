#include "sakls/SyntaxAPI.hpp"

using namespace sakls;

///===---------------------------------------------------------------------===//
/// SyntaxNode
///===---------------------------------------------------------------------===//

SyntaxNode::SyntaxNode() : cNode{.type = SAKLS_FICTIONAL_SYNTAX_NODE_TYPE} {}

SyntaxNode::SyntaxNode(sakls_SyntaxNode cNode) : cNode(cNode) {}

const char *SyntaxNode::getType() const { return cNode.type; }

///===---------------------------------------------------------------------===//
/// SyntaxAPIException
///===---------------------------------------------------------------------===//

SyntaxAPIException::SyntaxAPIException(std::string explanation)
    : std::runtime_error("Syntax API exception: " + explanation) {}

///===---------------------------------------------------------------------===//
/// SyntaxAPIRef
///===---------------------------------------------------------------------===//

SyntaxAPIRef::SyntaxAPIRef() : cAPI{.impl = nullptr} {}

SyntaxAPIRef::SyntaxAPIRef(sakls_SyntaxAPI cAPI) : cAPI(cAPI) {}

bool SyntaxAPIRef::initialized() const { return cAPI.impl; }

SyntaxStackRef SyntaxAPIRef::getSyntaxStack() const {
  SyntaxStackRef syntaxStack;
  if (cAPI.getSyntaxStack(cAPI.impl, &syntaxStack))
    throw SyntaxAPIException("getSyntaxStack failed");
  return syntaxStack;
}

void SyntaxAPIRef::destroy() {
  cAPI.destroy(cAPI.impl);
  cAPI.impl = nullptr;
}

///===---------------------------------------------------------------------===//
/// SyntaxAPI
///===---------------------------------------------------------------------===//

SyntaxAPI::SyntaxAPI(sakls_SyntaxAPI cAPI) : SyntaxAPIRef(std::move(cAPI)) {}

SyntaxAPI::~SyntaxAPI() {
  if (initialized())
    destroy();
}
