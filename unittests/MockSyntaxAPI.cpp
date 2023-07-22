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
              [](void *impl) {
                MockSyntaxAPI &_this = *reinterpret_cast<MockSyntaxAPI *>(impl);
                return SyntaxStackRef{.addr = _this.syntaxStack.data(),
                                      .size = _this.syntaxStack.size()};
              },
          .destroy = [](void *) {},
      } {}

SyntaxAPIRef MockSyntaxAPI::getAPI() const { return SyntaxAPIRef(cAPI); }

void MockSyntaxAPI::push(const char *syntaxNodeType) {
  syntaxStack.push_back({syntaxNodeType});
}

void MockSyntaxAPI::pop() { syntaxStack.pop_back(); }
