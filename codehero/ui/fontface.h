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
    int32_t left;
    int32_t top;
    uint32_t advanceX;
    std::shared_ptr<Texture> texture;
};

class FontFace {
public:
    FontFace(Font& iFont);
    virtual ~FontFace() {}

    FontFaceGlyph& GetGlyph(char iC);

protected:
    Font& m_rFont;
    std::map<uint32_t, FontFaceGlyph> m_Glyphs;
};

} // namespace CodeHero

#endif // CODEHERO_UI_FONTFACE_H_
