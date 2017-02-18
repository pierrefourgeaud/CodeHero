// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/text.h"

namespace CodeHero {

void Text::SetFont(const std::string& iFontName) {
    (void)iFontName;
}

void Text::SetFont(std::shared_ptr<Font> iFont) {
    (void)iFont;
}

void Text::SetSize(uint32_t iSize) {
    m_Size = iSize;
}

void Text::SetText(const std::string& iText) {
    m_Text = iText;
}

void Text::GetBatches(std::vector<UIBatch>& oBatches) {
    (void)oBatches;
}

} // namespace CodeHero

