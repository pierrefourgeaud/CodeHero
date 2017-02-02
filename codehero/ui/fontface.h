// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_FONTFACE_H_
#define CODEHERO_UI_FONTFACE_H_

#include <map>
#include <memory>
#include "core/typedefs.h"
#include "core/texture.h"

namespace CodeHero {

// Forward declaration
class Font;

struct FontFaceGlyph {
    uint32_t width;
    uint32_t height;
    uint8_t advanceX;
    std::unique_ptr<Texture> texture;
};

class FontFace {
public:
    FontFace(Font& iFont);
    virtual ~FontFace() {}

protected:
    Font& _GetFont() const { return m_rFont; }

private:
    Font& m_rFont;
    std::map<unsigned char, FontFaceGlyph> m_Glyphs;
};

} // namespace CodeHero

#endif // CODEHERO_UI_FONTFACE_H_
