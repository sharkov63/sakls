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

using SyntaxStackRef = ::sakls_SyntaxStackRef;

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
  /// \return Reference to the Syntax Stack
  /// \throws SyntaxAPIException
  SyntaxStackRef getSyntaxStack();
};

} // namespace sakls

#endif
