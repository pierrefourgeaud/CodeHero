// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/fontface_freetype.h"
#include <ft2build.h>
#include <cmath>
#include <cstdint>
#include "core/enginecontext.h"
#include "core/image.h"
#include "graphics/rendersystem.h"
#include "ui/font.h"
#include FT_FREETYPE_H
#include <logger.h>

namespace CodeHero {

FontFaceFreeType::FontFaceFreeType(Font& iFont, uint32_t iSize) : FontFace(iFont), m_Size(iSize) {
    _Load();
}

FontFaceFreeType::~FontFaceFreeType() {}

void FontFaceFreeType::_Load() {
    FT_Library library;
    if (FT_Init_FreeType(&library)) {
        LOGE << "FontFaceFreeType: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Memory_Face(library, m_rFont.GetBuffer().get(), m_rFont.GetBufferSize(), 0, &face)) {
        LOGE << "FontFaceFreeType: Failed to load the font" << std::endl;
        goto done_library;
    }

    if (FT_Set_Pixel_Sizes(face, 0, m_Size)) {
        LOGE << "FontFaceFreeType: Failed to set the size of the font" << std::endl;
        goto done;
    }

    {
        m_Ascender = std::floor((face->size->metrics.ascender >> 6) + 0.5f); // / 64
        m_MaxHeight = std::floor(
            ((face->size->metrics.ascender - face->size->metrics.descender) >> 6) + 0.5f);
        // List all glyph
        uint32_t numGlyphs = static_cast<uint32_t>(face->num_glyphs);
        std::vector<uint32_t> charCodes(numGlyphs, 0);

        {
            FT_UInt glyphIndex;
            FT_ULong charCode = FT_Get_First_Char(face, &glyphIndex);
            while (glyphIndex != 0) {
                if (glyphIndex < numGlyphs) {
                    charCodes[glyphIndex] = static_cast<uint32_t>(charCode);
                }

                charCode = FT_Get_Next_Char(face, charCode, &glyphIndex);
            }
        }

        // Load them all !
        for (unsigned int i = 0; i < numGlyphs; ++i) {
            unsigned int charCode = charCodes[i];
            if (charCode == 0) {
                continue;
            }

            FontFaceGlyph fontGlyph;
            if (!FT_Load_Char(face, charCode, FT_LOAD_RENDER)) {
                fontGlyph.width = face->glyph->bitmap.width;
                fontGlyph.height = face->glyph->bitmap.rows;
                fontGlyph.left = face->glyph->bitmap_left;
                fontGlyph.top = face->glyph->bitmap_top;
                fontGlyph.advanceX = face->glyph->advance.x;

                auto image = std::make_shared<Image>(m_rFont.GetContext());
                image->Create(fontGlyph.width, fontGlyph.height);
                uint8_t* dest = image->GetRawData();
                memcpy(dest, face->glyph->bitmap.buffer, image->GetSize());
                fontGlyph.texture =
                    m_rFont.GetContext()->GetSubsystem<RenderSystem>()->CreateTexture();
                fontGlyph.texture->Load(image);
                m_Glyphs[charCode] = std::move(fontGlyph);
            }
        }
    }

done:
    FT_Done_Face(face);
done_library:
    FT_Done_FreeType(library);
}

} // namespace CodeHero
