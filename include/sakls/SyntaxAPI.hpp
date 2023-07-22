///
/// \file SyntaxAPI.hpp
/// This file contains useful C++ wrappers
/// and convenience functions for the C SAKLS Syntax API.
///
#ifndef SAKLS_SYNTAX_API_HPP
#define SAKLS_SYNTAX_API_HPP

#include "sakls/SyntaxAPI.h"

#include <exception>

namespace sakls {

/// C++ wrapper around sakls_SyntaxNode.
class SyntaxNode {
  sakls_SyntaxNode cNode;

public:
  /// Create the fictional syntax node that lies just below the bottom
  /// of any syntax stack.
  SyntaxNode();

  /// Convert from C sakls_SyntaxNode. The conversion can be implicit.
  SyntaxNode(sakls_SyntaxNode cNode);

  /// A null-terminated string identifier of the type of this syntax node.
  const char *getType() const;
};

/// A non-owning reference to a syntax stack.
using SyntaxStackRef = ::sakls_SyntaxStackRef;

/// An exception which can be issued during a Syntax API call.
class SyntaxAPIException : public std::exception {};

/// A convenience C++ wrapper around sakls_SyntaxAPI.
///
/// This wrapper does not own the implementation of Syntax API:
/// when it is destroyed, it does not call destroy method of Syntax API.
class SyntaxAPIRef {
  /// Underlying C Syntax API structure.
  sakls_SyntaxAPI cAPI;

public:
  explicit SyntaxAPIRef(sakls_SyntaxAPI cAPI);

  /// Get Syntax Stack of the current position in the currently edited file.
  ///
  /// \return Reference to the Syntax Stack.
  /// \throws SyntaxAPIException
  SyntaxStackRef getSyntaxStack() const;
};

} // namespace sakls

#endif
