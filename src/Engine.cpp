#include "sakls/Engine.hpp"

using namespace sakls;

///===---------------------------------------------------------------------===//
/// Engine
///===---------------------------------------------------------------------===//

Engine::Engine(LayoutAPIRef layoutAPI, SyntaxAPIRef syntaxAPI)
    : layoutAPI(layoutAPI), syntaxAPI(syntaxAPI) {}

void Engine::updateNewSyntaxStack() {}
