///
/// \file SyntaxAPI.hpp
/// This file contains useful C++ wrappers
/// and convenience functions for the C SAKLS Syntax API.
///
#ifndef SAKLS_SYNTAX_API_HPP
#define SAKLS_SYNTAX_API_HPP

#include "sakls/SyntaxAPI.h"

#include <stdexcept>

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
class SyntaxAPIException : public std::runtime_error {
public:
  SyntaxAPIException(std::string explanation);
};

/// A convenience C++ wrapper around sakls_SyntaxAPI.
///
/// This wrapper does not own the implementation of Syntax API:
/// when it is destroyed, it does not call destroy method of Syntax API.
class SyntaxAPIRef {
protected:
  /// Underlying C Syntax API structure.
  sakls_SyntaxAPI cAPI;

public:
  /// Create uninitialized Syntax API reference.
  SyntaxAPIRef();

  /// Convert from C API.
  explicit SyntaxAPIRef(sakls_SyntaxAPI cAPI);

  /// \return true if referenced Syntax API is initialized with an
  /// implementation.
  bool initialized() const;

  /// Get the syntax stack of the current position in the currently edited file.
  ///
  /// \return Reference to the syntax stack.
  /// \throws SyntaxAPIException
  SyntaxStackRef getSyntaxStack() const;

  /// Destroy Syntax API.
  void destroy();
};

/// A convenience C++ wrapper around sakls_SyntaxAPI.
///
/// Unlike SyntaxAPIRef, this wrapper owns the implementation of Syntax API:
/// in its destructor it calls destroy method of Syntax API.
class SyntaxAPI : public SyntaxAPIRef {
public:
  explicit SyntaxAPI(sakls_SyntaxAPI cAPI);

  ~SyntaxAPI();
};

} // namespace sakls

#endif
