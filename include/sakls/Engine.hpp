///
/// \file Engine.hpp
///
#ifndef SAKLS_ENGINE_HPP
#define SAKLS_ENGINE_HPP

#include "EngineAPI.h"
#include "LayoutAPI.hpp"
#include "SyntaxAPI.hpp"

namespace sakls {

class Engine {
  LayoutAPIRef layoutAPI;
  SyntaxAPIRef syntaxAPI;

public:
  explicit Engine(LayoutAPIRef layoutAPI, SyntaxAPIRef syntaxAPI);

  void updateNewSyntaxStack();
};

} // namespace sakls

#endif
