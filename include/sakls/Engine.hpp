///
/// \file Engine.hpp
/// This file declares the SAKLS Engine.
///
#ifndef SAKLS_ENGINE_HPP
#define SAKLS_ENGINE_HPP

#include "sakls/Layout.hpp"
#include "sakls/Schema.hpp"
#include "sakls/Syntax.hpp"

#include <filesystem>
#include <optional>

namespace spdlog {

class logger;

} // namespace spdlog

namespace sakls {

/// \brief SAKLS engine: the key class that is actually responsible for
/// making decisions on switching keyboard layout.
///
/// When the contents or the cursor position of the currently edited file
/// change, the editor (or a plugin) makes calls to the Engine, passing syntax
/// information as parameters. Then, the engine makes the decision and sets the
/// chosen keyboard layout using the layout backend.
///
/// The algorithm, which tells the engine what keyboard layout to set at the
/// current moment, knowing syntax information, is described by Schema class.
class Engine {
public:
  /// @name Engine C++ API
  /// When modifying this, modify Engine C API as well.
  /// @{

  /// \brief Create a SAKLS engine.
  ///
  /// Created engine is inactive (see Engine state).
  ///
  /// \param layoutBackend Layout backend for the engine to use.
  /// \param schema High-level SAKLS schema, which configures the engine.
  /// \param translator Schema translator, which translates string syntax node
  /// types (seen in high-level schema) into integer syntax node types
  /// (used in Engine for computations). In case when the user is also aware
  /// about the translation, and passes integer syntax node types in calls to
  /// Engine API, the user must guarantee that this translation is valid during
  /// the whole lifetime of the Engine.
  Engine(ILayoutBackend &layoutBackend, Schema schema = Schema(),
         SchemaTranslator translator = SchemaTranslator()) noexcept;

  /// \brief Set the Engine state to inactive.
  void reset();

  /// \brief Set currently observed syntax node.
  ///
  /// \pre newNode must not be an ignored syntax node.
  ///
  /// This is a cheap way to update the Engine; it allows to directly set the
  /// current syntax node without passing the whole syntax stack. However, the
  /// user must guarantee that the new node is not an ignored syntax node.
  ///
  /// \param newNode New observed syntax node.
  /// \param force Change the layout even if the type of the current syntax node
  /// hasn't been changed.
  void setNewSyntaxNode(SyntaxNode newNode, bool force = false);

  /// \brief Replace the currently observed syntax stack with a new one.
  ///
  /// This is the most flexible way to update an Engine, but it is also the
  /// most expensive one: in the worst case it requires to traverse the whole
  /// syntax stack.
  ///
  /// \param synStack The new syntax stack.
  /// \param force Change the layout even if the type of the current syntax node
  /// hasn't been changed.
  void setNewSyntaxStack(SyntaxStackRef synStack, bool force = false);

  void setLogging(std::filesystem::path logFile);

  /// @}

protected:
  /// The layout backend, which handles layout switching demanded by the Engine.
  ILayoutBackend &layoutBackend;
  /// \brief Translates string syntax node types into integers.
  ///
  /// If user introduces new string syntax node types through Engine API,
  /// #translator will assign them new integers.
  SchemaTranslator translator;

  std::shared_ptr<spdlog::logger> logger;

  /// @name Engine State.
  /// At any point of time, a SAKLS engine can be either active, or inactive.
  /// When Engine is active, it observes a syntax node #node, which is (usually)
  /// the bottom of the currently observed syntax stack. When Engine is
  /// inactive, it does not observe any syntax node.
  /// @{

  /// \brief Currently observed syntax node.
  ///
  /// It is \p std::nullopt if and only if the Engine is inactive.
  std::optional<SyntaxNode> node;
  /// \brief Maps memorized syntax node types to their current layout.
  ///
  /// This mapping can be changed, after user manually switches
  /// the layout while being on a memorized syntax node.
  std::unordered_map<SyntaxNodeType, LayoutID> memorized;
  /// Maps forced syntax node types to their layout.
  std::unordered_map<SyntaxNodeType, LayoutID> forced;
  /// The set of ignored syntax node types.
  std::unordered_set<SyntaxNodeType> ignored;

  /// @}

  void keepUp();

  void setLayout(LayoutID layout);

  void configure(const Schema &schema);

  SyntaxNode getRelevantTop(SyntaxStackRef synStack) const;
};

} // namespace sakls

#endif
