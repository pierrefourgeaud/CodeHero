// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/font.h"
#include "core/fileaccess.h"
#include "core/filesystem.h"
#include "core/utils.h"
#include "ui/fontface.h"
#include "ui/fontface_freetype.h"

namespace CodeHero {

Font::Font(std::shared_ptr<EngineContext>& iContext, const std::string& iName)
    : m_pContext(iContext)
    , m_Name(iName) {}

std::shared_ptr<FontFace> Font::GetFace(uint32_t iSize) {
    _Load();

    auto face = m_Faces.find(iSize);
    if (face != m_Faces.end()) {
        return face->second;
    }

    std::string ext = FileSystem::GetExtension(m_Name);
    std::shared_ptr<FontFace> newFace;
    if (IsIn(ext, {"ttf", "otf", "woff"})) {
        m_Type = FontType::FT_FreeType;
        newFace.reset(new FontFaceFreeType(*this, iSize));
        m_Faces[iSize] = newFace;
    }

    return newFace;
}

void Font::_Load() {
    if (m_pFont != nullptr) {
        return;
    }

    FileAccess file;
    file.Open(m_Name, FileAccess::READ);
    int64_t size = file.GetSize();
    m_pFont = MakeSharedArray<uint8_t>(size);
    m_FontSize = size;
    file.Read(m_pFont.get(), size);
}

} // namespace CodeHero
