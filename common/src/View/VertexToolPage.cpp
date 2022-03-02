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

#include "VertexToolPage.h"

#include "View/MapDocument.h"
#include "View/ViewConstants.h"

#include <kdl/memory_utils.h>
#include <vecmath/vec.h>
#include <vecmath/vec_io.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "VertexTool.h"
#include "QtUtils.h"

namespace TrenchBroom {
namespace View {
VertexToolPage::VertexToolPage(std::weak_ptr<MapDocument> document, VertexTool& tool, QWidget* parent)
  : QWidget(parent)
  , m_document(document)
  , m_pickButton(nullptr)
  , m_applyButton(nullptr)
  , m_tool(tool)
  , m_color(Color(1.0f, 1.0f, 1.0f, 1.0f)) {
  createGui();
  connectObservers();
  updateGui();
}

void VertexToolPage::connectObservers() {
  auto document = kdl::mem_lock(m_document);
  m_notifierConnection +=
    document->selectionDidChangeNotifier.connect(this, &VertexToolPage::selectionDidChange);
}

void VertexToolPage::createGui() {
  m_pickButton = new QPushButton(tr("Pick"));
  m_applyButton = new QPushButton(tr("Apply"));
  m_colorButton = new ColorButton();
  m_colorButton->setColor(toQColor(m_color));

  connect(m_colorButton, &ColorButton::colorChangedByUser, this, [=](const QColor& color) {
    m_color = fromQColor(color);
  });

  connect(m_pickButton, &QAbstractButton::clicked, this, &VertexToolPage::pickColor);
  connect(m_applyButton, &QAbstractButton::clicked, this, &VertexToolPage::applyMove);

  auto* layout = new QHBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(LayoutConstants::MediumHMargin);

  layout->addWidget(m_pickButton, 0, Qt::AlignVCenter);
  layout->addWidget(m_applyButton, 0, Qt::AlignVCenter);
  layout->addWidget(m_colorButton, 0, Qt::AlignVCenter);
  layout->addStretch(1);

  setLayout(layout);
}

void VertexToolPage::updateGui() {
  auto document = kdl::mem_lock(m_document);
  m_pickButton->setEnabled(document->hasSelectedNodes());
  m_applyButton->setEnabled(document->hasSelectedNodes());
}

void VertexToolPage::selectionDidChange(const Selection&) {
  updateGui();
}

void VertexToolPage::applyMove() {
  m_tool.colorVertices(m_color);
}
void VertexToolPage::pickColor() {
  m_colorButton->blockSignals(true);
  m_colorButton->setColor(toQColor(m_tool.pickColor()));
  m_colorButton->blockSignals(false);
}
} // namespace View
} // namespace TrenchBroom
