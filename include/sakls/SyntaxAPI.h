///
/// \file SyntaxAPI.h
/// This file defines the C SAKLS Syntax API:
/// interface which provides syntax information of the currently edited file.
///
#ifndef SAKLS_SYNTAX_API_H
#define SAKLS_SYNTAX_API_H

#include "sakls/ExternC.h"

SAKLS_EXTERN_C_BEGIN

/// Identifies Syntax API version.
///
/// Upon making any ABI compatibility breaking changes in Syntax API,
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

/// A non-owning reference to a syntax stack.
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
  struct sakls_SyntaxNode *addr;

  /// Size of this syntax stack. Can be zero, which means that the stack is
  /// empty and its top is the fictional syntax node.
  unsigned long size;
};

/// Syntax API: C interface which provides syntax information of the currently
/// edited file to the SAKLS engine.
struct sakls_SyntaxAPI {
  /// An opaque pointer to the implementation of Syntax API,
  /// which is passed to every method.
  ///
  /// If it is null, then the Syntax API is invalid. For example, an error
  /// happened while producing the implementation.
  void *impl;

  /// Get the syntax stack for the current cursor position.
  ///
  /// \param impl Pointer to the implementation of Syntax API.
  /// \param[out] syntaxStack
  /// \return zero on success; non-zero value on error.
  int (*getSyntaxStack)(void *impl, struct sakls_SyntaxStackRef *syntaxStack);

  /// Destroy the implementation of Syntax API, free all the resources it owns.
  ///
  /// \param impl Pointer to the implementation of Syntax API.
  void (*destroy)(void *impl);
};

SAKLS_EXTERN_C_END

#endif
