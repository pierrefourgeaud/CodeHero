// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/label.h"
#include "core/enginecontext.h"
#include "graphics/rendersystem.h"
#include "graphics/vertexbuffer.h"
#include "ui/font.h"
#include "ui/fontface.h"
#include "ui/stylesheet.h"
#include "ui/uidraw.h"

namespace CodeHero {

Label::Label(std::shared_ptr<EngineContext>& iContext)
    : UIElement(iContext) {}

void Label::SetText(const std::string& iText) {
    m_Text = iText;
}

void Label::GetBatches(std::vector<UIBatch>& oBatches) {
    UIDraw::Text(m_pContext, oBatches, m_Text,
                 m_pStyle->GetDefault().defaultFontFace, m_Position, m_pStyle->GetDefault().fontColor);
}

} // namespace CodeHero

