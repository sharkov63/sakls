#include "sakls/EngineAPI.h"
#include "sakls/Engine.hpp"
#include "sakls/SyntaxAPI.hpp"

using namespace sakls;

void *sakls_engine_new(sakls_LayoutAPI cLayoutAPI, sakls_SyntaxAPI cSyntaxAPI) {
  return new Engine(LayoutAPIRef(cLayoutAPI), SyntaxAPIRef(cSyntaxAPI));
}

void sakls_engine_delete(void *engine) {
  delete reinterpret_cast<Engine *>(engine);
}

void sakls_engine_updateNewSyntaxStack(void *engine) {
  reinterpret_cast<Engine *>(engine)->updateNewSyntaxStack();
}
