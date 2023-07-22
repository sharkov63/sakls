#include "MockSyntaxAPI.hpp"

using namespace sakls;
using namespace sakls::unittests;

///===---------------------------------------------------------------------===//
/// MockSyntaxAPI
///===---------------------------------------------------------------------===//

MockSyntaxAPI::MockSyntaxAPI()
    : cAPI{
          .impl = this,
          .getSyntaxStack =
              [](void *impl, SyntaxStackRef *syntaxStack) {
                MockSyntaxAPI &_this = *reinterpret_cast<MockSyntaxAPI *>(impl);
                *syntaxStack = SyntaxStackRef{.addr = _this.syntaxStack.data(),
                                              .size = _this.syntaxStack.size()};
                return 0;
              },
          .destroy = [](void *) {},
      } {}

SyntaxAPIRef MockSyntaxAPI::getAPI() const { return SyntaxAPIRef(cAPI); }

void MockSyntaxAPI::push(const char *syntaxNodeType) {
  syntaxStack.push_back({syntaxNodeType});
}

void MockSyntaxAPI::pop() { syntaxStack.pop_back(); }
