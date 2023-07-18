#include "sakls/SyntaxAPI.hpp"

using namespace sakls;

///===---------------------------------------------------------------------===//
/// SyntaxAPIRef
///===---------------------------------------------------------------------===//

SyntaxAPIRef::SyntaxAPIRef(sakls_SyntaxAPI cAPI) : cAPI(cAPI) {}

SyntaxStackRef SyntaxAPIRef::getSyntaxStack() {
  SyntaxStackRef syntaxStack = cAPI.getSyntaxStack(cAPI.impl);
  if (!syntaxStack.addr)
    throw SyntaxAPIException();
  return syntaxStack;
}
