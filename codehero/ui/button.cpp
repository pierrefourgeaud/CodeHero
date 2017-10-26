// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/button.h"
#include "ui/uidraw.h"

namespace CodeHero {

Button::Button(std::shared_ptr<EngineContext>& iContext)
    : UIElement(iContext) {}

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
    Vector2 p1(x,     y);
    Vector2 p2(x + w, y);
    Vector2 p3(x + w, y + h);
    Vector2 p4(x,     y + h);

    // Batch
    UIDraw::Path(m_pContext, oBatches, {p1, p2, p3, p4});
}

} // namespace CodeHero

