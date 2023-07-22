#ifndef SAKLS_UNITTESTS_MOCK_SYNTAX_API_HPP
#define SAKLS_UNITTESTS_MOCK_SYNTAX_API_HPP

#include "sakls/SyntaxAPI.h"
#include "sakls/SyntaxAPI.hpp"

#include <vector>

namespace sakls::unittests {

/// Mock implementation of Syntax API for unit-testing.
class MockSyntaxAPI {
  std::vector<sakls_SyntaxNode> syntaxStack;
  sakls_SyntaxAPI cAPI;

public:
  MockSyntaxAPI();

  /// Get C++ Syntax API reference.
  SyntaxAPIRef getAPI() const;

  /// Push a syntax node with given type on the syntax stack.
  void push(const char *syntaxNodeType);

  /// Pop a syntax node from the syntax stack.
  void pop();
};

} // namespace sakls::unittests

#endif
