///
/// \file Instance.hpp
///
#ifndef SAKLS_INSTANCE_HPP
#define SAKLS_INSTANCE_HPP

#include "sakls/Engine.hpp"
#include "sakls/LayoutAPI.hpp"
#include "sakls/SyntaxAPI.hpp"

namespace sakls {

/// An Instance of SAKLS: object which owns and manages
/// everything necessary for SAKLS.
class Instance {
public:
  std::unique_ptr<LayoutAPI> layoutAPI;
  SyntaxAPI syntaxAPI;
  Engine engine;
};

} // namespace sakls

#endif
