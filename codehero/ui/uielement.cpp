// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/uielement.h"

namespace CodeHero {

UIElement::UIElement(std::shared_ptr<RenderSystem> iRS)
    : m_pRS(iRS) {}

void UIElement::AddChild(std::shared_ptr<UIElement> iElement) {
    m_Elements.push_back(iElement);
}

void UIElement::SetPosition(const Vector2& iPos) {
    m_Position = iPos;
}

void UIElement::SetPosition(float iWidth, float iHeight) {
    m_Position = {iWidth, iHeight};
}

} // namespace CodeHero

