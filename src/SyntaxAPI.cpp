#include "sakls/SyntaxAPI.hpp"

using namespace sakls;

///===---------------------------------------------------------------------===//
/// SyntaxNode
///===---------------------------------------------------------------------===//

SyntaxNode::SyntaxNode() : cNode{.type = SAKLS_FICTIONAL_SYNTAX_NODE_TYPE} {}

SyntaxNode::SyntaxNode(sakls_SyntaxNode cNode) : cNode(cNode) {}

const char *SyntaxNode::getType() const { return cNode.type; }

///===---------------------------------------------------------------------===//
/// SyntaxAPIRef
///===---------------------------------------------------------------------===//

SyntaxAPIRef::SyntaxAPIRef(sakls_SyntaxAPI cAPI) : cAPI(cAPI) {}

SyntaxStackRef SyntaxAPIRef::getSyntaxStack() const {
  SyntaxStackRef syntaxStack = cAPI.getSyntaxStack(cAPI.impl);
  return syntaxStack;
}
