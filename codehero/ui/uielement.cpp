// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/uielement.h"

namespace CodeHero {

UIElement::UIElement(std::shared_ptr<EngineContext>& iContext)
    : m_pContext(iContext) {}

void UIElement::AddChild(std::shared_ptr<UIElement> iElement) {
    m_Elements.push_back(iElement);
    iElement->SetParent(shared_from_this());
}

void UIElement::SetParent(const std::shared_ptr<UIElement>& iParent) {
    m_pParent = iParent;

    // TODO(pierre) We should be more precise to avoid overriding previously
    // set settings. Maybe a merge between that style and parent style would be best
    if (!m_pStyle) {
        m_pStyle = iParent->GetStyle();
    }

    // Add the offset with parent
    if (!iParent->IsRoot()) {
        m_Position = m_Position + iParent->GetLayoutPosition();
    }
}

void UIElement::SetPosition(const Vector2& iPos) {
    // If we have a parent and not root
    if (GetParent() && !GetParent()->IsRoot()) {
        m_Position = iPos + GetParent()->GetLayoutPosition();
    } else {
        m_Position = iPos;
    }
}

void UIElement::SetPosition(float iWidth, float iHeight) {
    // If we have a parent and not root
    if (GetParent() && !GetParent()->IsRoot()) {
        Vector2 pos(iWidth, iHeight);
        m_Position = pos + GetParent()->GetLayoutPosition();
    } else {
        m_Position = {iWidth, iHeight};
    }
}

} // namespace CodeHero

