/*
 Copyright (C) 2021 Kristian Duske

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

#include "MoveHandleDragTracker.h"

#include "Macros.h"

namespace TrenchBroom {
namespace View {
void MoveHandleDragTrackerDelegate::mouseScroll(const InputState&, const DragState&) {}
void MoveHandleDragTrackerDelegate::setRenderOptions(
  const InputState&, Renderer::RenderContext&) const {}
void MoveHandleDragTrackerDelegate::render(
  const InputState&, const DragState&, Renderer::RenderContext&, Renderer::RenderBatch&) const {}

DragHandleSnapper makeDragHandleSnapperFromSnapMode(const Grid& grid, const SnapMode snapMode) {
  switch (snapMode) {
    case SnapMode::Relative:
      return makeRelativeHandleSnapper(grid);
    case SnapMode::Absolute:
      return makeAbsoluteHandleSnapper(grid);
      switchDefault();
  }
}
} // namespace View
} // namespace TrenchBroom
