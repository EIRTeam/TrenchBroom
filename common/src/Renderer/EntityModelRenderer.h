/*
 Copyright (C) 2010-2017 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Color.h"
#include "Renderer/Renderable.h"

#include <unordered_map>

namespace TrenchBroom {
class Logger;

namespace Assets {
class EntityModelManager;
}

namespace Model {
class EditorContext;
class EntityNode;
} // namespace Model

namespace Renderer {
class RenderBatch;
class ShaderConfig;
class TexturedRenderer;

class EntityModelRenderer : public DirectRenderable {
private:
  Logger& m_logger;

  Assets::EntityModelManager& m_entityModelManager;
  const Model::EditorContext& m_editorContext;

  std::unordered_map<const Model::EntityNode*, TexturedRenderer*> m_entities;

  bool m_applyTinting;
  Color m_tintColor;

  bool m_showHiddenEntities;

public:
  EntityModelRenderer(
    Logger& logger, Assets::EntityModelManager& entityModelManager,
    const Model::EditorContext& editorContext);
  ~EntityModelRenderer() override;

  template <typename I> void setEntities(I cur, I end) {
    clear();
    addEntities(cur, end);
  }

  template <typename I> void addEntities(I cur, I end) {
    while (cur != end) {
      addEntity(*cur);
      ++cur;
    }
  }

  template <typename I> void updateEntities(I cur, I end) {
    while (cur != end) {
      updateEntity(*cur);
      ++cur;
    }
  }

  void addEntity(const Model::EntityNode* entityNode);
  void removeEntity(const Model::EntityNode* entityNode);
  void updateEntity(const Model::EntityNode* entityNode);
  void clear();

  bool applyTinting() const;
  void setApplyTinting(const bool applyTinting);
  const Color& tintColor() const;
  void setTintColor(const Color& tintColor);

  bool showHiddenEntities() const;
  void setShowHiddenEntities(bool showHiddenEntities);

  void render(RenderBatch& renderBatch);

private:
  void doPrepareVertices(VboManager& vboManager) override;
  void doRender(RenderContext& renderContext) override;
};
} // namespace Renderer
} // namespace TrenchBroom
