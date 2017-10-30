// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/stylesheet.h"
#include "ui/font.h"

namespace CodeHero {

Stylesheet::Stylesheet(const std::shared_ptr<EngineContext>& iContext)
    : m_pContext(iContext) {
    _Initialize();
}

void Stylesheet::_Initialize() {
    m_Default.fontFamily = std::make_shared<Font>(m_pContext, "./resources/fonts/Montserrat-Regular.ttf");
    m_Default.fontSize = 20;
    m_Default.fontColor = Color::White;
    m_Default.backgroundColor = {0.145f, 0.1725f, 0.247f, 1.0f};
    m_Default.borderColor = {0.1137f, 0.1254f, 0.1607f, 1.0f};
    m_Default.defaultFontFace = m_Default.fontFamily->GetFace(m_Default.fontSize);

    m_Hover = m_Default;
    m_Active = m_Default;
}

} // namespace CodeHero