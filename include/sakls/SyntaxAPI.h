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
/// Upon making any ABI-breaking changes in Syntax API,
/// this number has to be incremented.
///
/// FIXME: upon release start this with 1
#define SAKLS_SYNTAX_API_VERSION 0

/// Syntax Node: an entry in a Syntax Stack.
struct sakls_SyntaxNode {
  /// A null-terminated string identifier of a Syntax Node type.
  const char *type;
};

/// A reference to a Syntax Stack.
///
/// Let's say in the external editor we are editing a file \p f, and the syntax
/// tree \p T of file \p f is maintained (either by the editor, or by some
/// plugin within the editor). Let \p p be a position in file \p f.
/// Then, the syntax stack of position \p p in file \p f is the
/// vertical path in syntax tree \p T from the lowest node containing position
/// to the root of the tree. The top of the stack is the lowest node, and the
/// bottom is the root of \p T.
///
/// A Syntax Stack is laid out as an array, with the first element being the
/// root node, and the last element being the lowest node.
///
/// An element of a Syntax Stack is called a Syntax Node, it's represented by
/// sakls_SyntaxNode structure.
struct sakls_SyntaxStackRef {
  /// Address of the first element in the array representation of this Syntax
  /// Stack, which corresponds to the bottom of the stack.
  sakls_SyntaxNode *addr;

  /// Size of the Syntax Stack. Required to be greater than zero at all times.
  unsigned long size;
};

/// Syntax API: C interface which provides syntax information of the currently
/// edited file to the SAKLS engine.
///
/// When the contents or the cursor position of the currently edited file
/// changes, the editor (or the plugin to the editor) makes event calls to the
/// SAKLS engine, which in turn calls Syntax API to get the relevant syntax
/// information.
struct sakls_SyntaxAPI {
  /// An opaque pointer to the implementation of Syntax API,
  /// which is passed to every method.
  ///
  /// If it is NULL, then the Syntax API is invalid. For example, an error
  /// happened while producing the implementation.
  void *const impl;

  /// Get Syntax Stack at the current cursor position.
  ///
  /// \param impl Pointer to the implementation of Syntax API.
  /// \return Reference to the Syntax Stack. On error, the \p addr field
  /// of the reference structure is zero.
  sakls_SyntaxStackRef (*getSyntaxStack)(void *impl);

  /// Destroy the implementation of Syntax API, free all the resources it owns.
  ///
  /// \param impl Pointer to the implementation of Syntax API.
  void (*destroy)(void *impl);
};

SAKLS_EXTERN_C_END

#endif
