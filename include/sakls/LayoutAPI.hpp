///
/// \file LayoutAPI.hpp
///
#ifndef SAKLS_LAYOUT_API_HPP
#define SAKLS_LAYOUT_API_HPP

#include "sakls/LayoutAPI.h"

#include <exception>

namespace sakls {

using LayoutID = ::sakls_LayoutID;

/// A convenience C++ wrapper over sakls_LayoutAPI.
///
/// It owns the implementation of Layout API, calling destroy in its destructor.
class LayoutAPI {
  sakls_LayoutAPI cAPI;

public:
  explicit LayoutAPI(sakls_LayoutAPI &&cAPI);

  ~LayoutAPI();

  LayoutID getLayout() const;

  void setLayout(LayoutID layout);

  class LayoutAPIException : std::exception {};
};

} // namespace sakls

#endif
