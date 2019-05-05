// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/fontface.h"
#include <exception>

namespace CodeHero {

FontFace::FontFace(Font& iFont) : m_rFont(iFont) {}

FontFaceGlyph& FontFace::GetGlyph(char iC) {
    auto c = m_Glyphs.find(iC);
    if (c == m_Glyphs.end()) {
        throw std::range_error("Glyph not found");
    }

    return c->second;
}

} // namespace CodeHero