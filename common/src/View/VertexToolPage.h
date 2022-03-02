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

#include "NotifierConnection.h"

#include <memory>

#include <QWidget>
#include "View/ColorButton.h"
#include "Color.h"

class QAbstractButton;
class QLineEdit;

namespace TrenchBroom {
namespace View {
class MapDocument;
class Selection;
class VertexTool;

class VertexToolPage : public QWidget {
  Q_OBJECT
private:
  std::weak_ptr<MapDocument> m_document;

  QAbstractButton* m_pickButton;
  QAbstractButton* m_applyButton;
  ColorButton* m_colorButton;
  VertexTool& m_tool;
  Color m_color;

public:
  explicit VertexToolPage(std::weak_ptr<MapDocument> document, VertexTool& tool, QWidget* parent = nullptr);

private:
  NotifierConnection m_notifierConnection;

  void selectionDidChange(const Selection& selection);
  void connectObservers();

  void createGui();
  void updateGui();
  void pickColor();
  void applyMove();
};
} // namespace View
} // namespace TrenchBroom
