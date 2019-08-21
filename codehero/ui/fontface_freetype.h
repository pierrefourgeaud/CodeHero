// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_FONTFACE_FREETYPE_H_
#define CODEHERO_UI_FONTFACE_FREETYPE_H_

#include "ui/fontface.h"

namespace CodeHero {

class FontFaceFreeType : public FontFace {
public:
    FontFaceFreeType(Font& iFont, uint32_t iSize);
    ~FontFaceFreeType();

private:
    uint32_t m_Size;

    void _Load();
};

} // namespace CodeHero

#endif // CODEHERO_UI_FONTFACE_FREETYPE_H_
