///
/// \file Syntax.hpp
/// Useful C++ wrappers of C syntax stack definition.
///
#ifndef SAKLS_SYNTAX_HPP
#define SAKLS_SYNTAX_HPP

#include "sakls-c/Syntax.h"

#include <initializer_list>
#include <iterator>
#include <span>

namespace sakls {

/// C++ wrapper around sakls_SyntaxNode.
class SyntaxNode {
  sakls_SyntaxNode cNode;

public:
  /// Create the fictional syntax node that lies just below the bottom
  /// of any syntax stack.
  SyntaxNode() : cNode{.type = SAKLS_FICTIONAL_SYNTAX_NODE_TYPE} {}

  /// Create node with a type.
  SyntaxNode(const char *nodeType) : cNode{.type = nodeType} {}

  /// Convert from C sakls_SyntaxNode. The conversion can be implicit.
  SyntaxNode(sakls_SyntaxNode cNode) : cNode(cNode) {}

  /// A null-terminated string identifier of the type of this syntax node.
  const char *getType() const { return cNode.type; }
};

/// A non-owning reference to a syntax stack:
/// a convenience STL-like container wrapper around sakls_SyntaxStackRef.
///
/// This type is small and shall be passed by value, not by reference.
class SyntaxStackRef : public std::span<const SyntaxNode> {
public:
  using std::span<const SyntaxNode>::span;

  SyntaxStackRef(sakls_SyntaxStackRef cRef)
      : std::span<const SyntaxNode>(
            reinterpret_cast<const SyntaxNode *>(cRef.data), cRef.size) {}

#if defined(__GNUC__) && (__GNUC__ >= 9)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winit-list-lifetime"
#endif
  SyntaxStackRef(const std::initializer_list<SyntaxNode> &list)
      : SyntaxStackRef(list.begin() != list.end() ? list.begin() : nullptr,
                       list.size()) {}
#if defined(__GNUC__) && (__GNUC__ >= 9)
#pragma GCC diagnostic pop
#endif
};

} // namespace sakls

#endif
