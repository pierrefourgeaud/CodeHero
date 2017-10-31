// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/window.h"
#include <cmath>
#include "core/assert.h"
#include "ui/font.h"
#include "ui/fontface.h"
#include "ui/stylesheet.h"
#include "ui/uidraw.h"

namespace CodeHero {

Window::Window(std::shared_ptr<EngineContext>& iContext)
    : UIElement(iContext) {}

void Window::SetHeader(const std::string& iText) {
    CH_ASSERT(m_Flags ^ Window::Flags::F_NoHeader);

    m_HeaderText = iText;
}

void Window::SetSize(const Vector2& iSize) {
    m_Size = iSize;
}

const Vector2& Window::GetSize() const {
    return m_Size;
}

Vector2 Window::GetLayoutPosition() const {
    return {m_Position.x(), m_Position.y() + 50.0f};
}

void Window::GetBatches(std::vector<UIBatch>& oBatches) {
    float x = m_Position.x();
    float y = m_Position.y();
    float w = m_Size.x();
    float h = m_Size.y();

    // TODO(pierre) - Compute the header's height with padding and text size
    //              - Also the window is not always with a header
    const float headerHeight = (m_Flags & F_NoHeader) ? 0.0f : 50.0f;
    Vector2 p1(x,     y + headerHeight);
    Vector2 p2(x + w, y + headerHeight);
    Vector2 p3(x + w, y + h);
    Vector2 p4(x,     y + h);

    if (m_Flags ^ F_NoHeader) {
        Vector2 p1b(x,     y);
        Vector2 p2b(x + w, y);
        // TODO(pierre) This should be save in a local style
        std::shared_ptr<FontFace> fa = m_pStyle->GetDefault().fontFamily->GetFace(24);
        const float topH = std::floor((headerHeight - fa->GetMaxHeight()) / 2.0f + 0.5f);

        // Header
        UIDraw::Text(m_pContext, oBatches, "Info", fa, {x + 15.0f, y + topH}, m_pStyle->GetDefault().fontColor);
        UIDraw::PathStroke(m_pContext, oBatches, { p1b, p2b, p2, p1 }, m_pStyle->GetDefault().borderColor);
        UIDraw::PathFill(m_pContext, oBatches, { p1b, p2b, p2, p1 }, m_pStyle->GetDefault().backgroundColor);
    }
    // Body
    UIDraw::PathStroke(m_pContext, oBatches, { p1, p2, p3, p4 }, m_pStyle->GetDefault().borderColor);
    UIDraw::PathFill(m_pContext, oBatches, { p1, p2, p3, p4 }, m_pStyle->GetDefault().backgroundColor);
}

} // namespace CodeHero