// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/button.h"
#include "ui/stylesheet.h"
#include "ui/uidraw.h"

namespace CodeHero {

Button::Button(std::shared_ptr<EngineContext>& iContext) : UIElement(iContext) {}

void Button::SetText(const std::string& iText) {
    m_Text = iText;
}

void Button::SetSize(const Vector2& iSize) {
    m_Size = iSize;
}

const Vector2& Button::GetSize() const {
    return m_Size;
}

void Button::GetBatches(std::vector<UIBatch>& oBatches) {
    float x = m_Position.x();
    float y = m_Position.y();
    float w = m_Size.x();
    float h = m_Size.y();
    Vector2 p1(x, y);
    Vector2 p2(x + w, y);
    Vector2 p3(x + w, y + h);
    Vector2 p4(x, y + h);

    std::vector<Vector2> points;
    float radius = 10;
    UIDraw::GetPointListArc(points, {x + radius, y + radius}, radius, 6, 9);
    UIDraw::GetPointListArc(points, {p3.x() - radius, y + radius}, radius, 9, 12);
    UIDraw::GetPointListArc(points, {p3.x() - radius, p3.y() - radius}, radius, 0, 3);
    UIDraw::GetPointListArc(points, {x + radius, p3.y() - radius}, radius, 3, 6);

    // Batch
    UIDraw::PathFill(m_pContext, oBatches, points, m_pStyle->GetDefault().backgroundColor);
    UIDraw::PathStroke(m_pContext, oBatches, points, m_pStyle->GetDefault().borderColor);
}

} // namespace CodeHero
