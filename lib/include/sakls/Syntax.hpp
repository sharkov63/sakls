///
/// \file Syntax.hpp
/// Useful C++ wrappers of C syntax stack definition.
///
#ifndef SAKLS_LIB_SYNTAX_HPP
#define SAKLS_LIB_SYNTAX_HPP

#include "sakls/CAPI/Syntax.h"

#include <initializer_list>
#include <iterator>

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
class SyntaxStackRef {
public:
  using value_type = SyntaxNode;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = const_pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

private:
  const SyntaxNode *data_;

  size_t size_;

public:
  SyntaxStackRef() : data_(nullptr), size_(0) {}

  SyntaxStackRef(const SyntaxNode *data, size_t size)
      : data_(data), size_(size) {}

  SyntaxStackRef(sakls_SyntaxStackRef cRef)
      : data_(reinterpret_cast<SyntaxNode *>(cRef.data)), size_(cRef.size) {}

#if defined(__GNUC__) && (__GNUC__ >= 9)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winit-list-lifetime"
#endif
  SyntaxStackRef(const std::initializer_list<SyntaxNode> &list)
      : data_(list.begin() != list.end() ? list.begin() : nullptr),
        size_(list.size()) {}
#if defined(__GNUC__) && (__GNUC__ >= 9)
#pragma GCC diagnostic pop
#endif

  iterator begin() const { return data_; }
  iterator end() const { return data_ + size_; }

  reverse_iterator rbegin() const { return reverse_iterator(end()); }
  reverse_iterator rend() const { return reverse_iterator(begin()); }

  bool empty() const { return size_ == 0; }

  const SyntaxNode *data() { return data_; }

  size_t size() const { return size_; }
};

} // namespace sakls

#endif
