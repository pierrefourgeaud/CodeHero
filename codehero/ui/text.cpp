// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/text.h"
#include "core/enginecontext.h"
#include "graphics/rendersystem.h"
#include "graphics/vertexbuffer.h"
#include "ui/font.h"
#include "ui/fontface.h"
#include "ui/uidraw.h"

namespace CodeHero {

Text::Text(std::shared_ptr<EngineContext>& iContext)
    : UIElement(iContext) {}

void Text::SetFont(const std::string& iFontName) {
    (void)iFontName;
}

void Text::SetFont(std::shared_ptr<Font> iFont) {
    m_pFont = iFont;
}

void Text::SetSize(uint32_t iSize) {
    m_Size = iSize;
}

void Text::SetText(const std::string& iText) {
    m_Text = iText;
}

void Text::SetColor(const Color& iColor) {
    m_Color = iColor;
}

void Text::GetBatches(std::vector<UIBatch>& oBatches) {
    if (m_pFont.get() && m_Size != 0) {
        std::shared_ptr<FontFace> fa = m_pFont->GetFace(m_Size);
        UIDraw::Text(m_pContext, oBatches, m_Text, fa, m_Position, m_Color);
    }
}

} // namespace CodeHero

