///
/// \file Syntax.h
/// Syntax API: contains C definition of syntax stack.
///
#ifndef SAKLS_C_SYNTAX_H
#define SAKLS_C_SYNTAX_H

#include "sakls-c/ExternC.h"

#include <stddef.h>

SAKLS_EXTERN_C_BEGIN

/// \brief Identifies syntax API version.
///
/// Upon making any ABI compatibility breaking changes in syntax API,
/// this number has to be incremented.
///
/// TODO: upon release start this with 1
#define SAKLS_SYNTAX_API_VERSION 0

/// The type of the fictional syntax node that lies
/// just below the bottom of any syntax stack.
#define SAKLS_FICTIONAL_SYNTAX_NODE_TYPE ""

/// Syntax node: an entry in a syntax stack.
struct sakls_SyntaxNode {
  /// A null-terminated string identifier of the type of this syntax node.
  const char *type;
};

/// \brief A non-owning reference to a syntax stack.
///
/// Let's say in the external editor we are editing a file \p f, and the syntax
/// tree \p T of file \p f is maintained (either by the editor, or by some
/// plugin within the editor). Let \p p be a position in file \p f.
/// Then, the syntax stack of position \p p in file \p f is the
/// vertical path in syntax tree \p T from the lowest node containing
/// position \p p to the root of the tree. That is, that lowest node corresponds
/// to the top of the stack and the root corresponds to the bottom of the stack.
///
/// An element of a syntax stack is called a syntax node; it's represented by
/// sakls_SyntaxNode structure.
///
/// A syntax stack is laid out as an array, with the first element being the
/// root node, and the last element being the lowest node.
///
/// Please note that a syntax stack is assumed to hold an additional fictional
/// syntax node just below the bottom; its' type is equal to
/// SAKLS_FICTIONAL_SYNTAX_NODE_TYPE. So, if a syntax stack is empty, then it's
/// top is actually that fictional node.
struct sakls_SyntaxStackRef {
  /// Address of the first element in the array representation of this syntax
  /// stack, which corresponds to the bottom of the stack. If \p size is zero,
  /// this is allowed to be null.
  struct sakls_SyntaxNode *data;

  /// Size of this syntax stack. Can be zero, which means that the stack is
  /// empty and its top is the fictional syntax node.
  size_t size;
};

SAKLS_EXTERN_C_END

#endif
