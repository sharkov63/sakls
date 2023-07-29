///
/// \file Engine.hpp
/// This file declares the SAKLS Engine.
///
#ifndef SAKLS_ENGINE_HPP
#define SAKLS_ENGINE_HPP

#include "sakls/LayoutAPI.hpp"
#include "sakls/Schema.hpp"
#include "sakls/Syntax.hpp"

#include <optional>

namespace sakls {

/// SAKLS engine: the key class that is actually responsible for
/// making decisions on switching keyboard layout.
///
/// When the contents or the cursor position of the currently edited file
/// change, the editor (or a plugin) makes calls to the SAKLS engine
/// (TODO insert a reference to the API through which the calls are made),
/// passing the syntax information as parameters. Then, the engine makes the
/// decision and sets the chosen keyboard layout via layout API.
///
/// The algorithm, which tells the engine what keyboard layout to set at the
/// current moment, knowing syntax information, is described by Schema class.
///
/// Note that Engine does not take ownership of layout API,
/// but it does that of the schema.
class Engine {
  LayoutAPIRef layoutAPI;
  Schema schema;

  std::optional<SyntaxNode> current;

  SyntaxNode getRelevantTop(SyntaxStackRef synStack) const;

  void saveCurrentMemorized();

  void updateNewSyntaxNode(SyntaxNode newNode, bool force = false);

public:
  /// Create a SAKLS engine.
  ///
  /// The created SAKLS engine has uninitialized state:
  /// it does not observe any syntax stack. To initialize it,
  /// call an update method.
  ///
  /// \param layoutAPI Reference to layout API implementation.
  /// \param schema SAKLS schema (passed by value).
  Engine(LayoutAPIRef layoutAPI, Schema schema);

  /// Update the SAKLS engine: completely replace the currently observed syntax
  /// stack with a new one.
  ///
  /// This is the most flexible way to update a SAKLS engine, but it is also the
  /// most expensive one: in the worst case it requires to traverse the whole
  /// syntax stack.
  ///
  /// \param synStack The new syntax stack.
  /// \param force Change the layout even if the type of the current syntax node
  /// hasn't been changed.
  void updateNewSyntaxStack(SyntaxStackRef synStack, bool force = false);
};

} // namespace sakls

#endif
