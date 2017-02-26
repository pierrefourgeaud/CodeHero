// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_FONT_H_
#define CODEHERO_UI_FONT_H_

#include <map>
#include <memory>
#include <string>

namespace CodeHero {

// Forward declaration
class FontFace;
class EngineContext;

enum class FontType : int32_t {
    FT_FreeType,
    FT_BitMap,
    FT_None
};

class Font {
public:
    Font(std::shared_ptr<EngineContext>& iContext, const std::string& iName);
    ~Font() {}

    std::shared_ptr<FontFace> GetFace(uint32_t iSize);

    std::shared_ptr<uint8_t> GetBuffer() const { return m_pFont; }
    int64_t GetBufferSize() const { return m_FontSize; }

    std::shared_ptr<EngineContext> GetContext() { return m_pContext; }

private:
    std::shared_ptr<EngineContext> m_pContext;
    std::string m_Name;
    std::shared_ptr<uint8_t> m_pFont;
    int64_t m_FontSize;

    FontType m_Type = FontType::FT_None;
    std::map<int, std::shared_ptr<FontFace>> m_Faces;

    void _Load();
};

} // namespace CodeHero

#endif // CODEHERO_UI_FONT_H_
