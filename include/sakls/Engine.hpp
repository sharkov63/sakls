///
/// \file Engine.hpp
/// This file declares the SAKLS Engine.
///
#ifndef SAKLS_ENGINE_HPP
#define SAKLS_ENGINE_HPP

#include "sakls/Layout.hpp"
#include "sakls/Schema.hpp"
#include "sakls/Syntax.hpp"

#include <optional>

namespace sakls {

/// SAKLS engine: the key class that is actually responsible for
/// making decisions on switching keyboard layout.
///
/// When the contents or the cursor position of the currently edited file
/// change, the editor (or a plugin) makes calls to the SAKLS engine,
/// passing the syntax information as parameters. Then, the engine makes the
/// decision and sets the chosen keyboard layout using the layout backend.
///
/// The algorithm, which tells the engine what keyboard layout to set at the
/// current moment, knowing syntax information, is described by Schema class.
///
/// Note that Engine does not take ownership of layout backend and schema.
class Engine {
  ILayoutBackend &layoutBackend;
  SchemaTranslator translator;

  std::unordered_map<SyntaxNodeType, LayoutID> memorized;
  std::unordered_map<SyntaxNodeType, LayoutID> forced;
  std::unordered_set<SyntaxNodeType> ignored;

  std::optional<SyntaxNode> current;

  void configure(const Schema &schema);

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
  /// \param layoutBackend Reference to the layout backend.
  /// \param schema High-level SAKLS schema.
  /// \param translator Schema translator valid for the time being.
  Engine(ILayoutBackend &layoutBackend, const Schema &schema = Schema(),
         SchemaTranslator translator = SchemaTranslator()) noexcept;

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
  void updateNewSyntaxStack(SyntaxStackRef synStack,
                            bool force = false) noexcept;
};

} // namespace sakls

#endif
