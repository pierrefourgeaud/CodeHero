// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_STYLESHEET_H_
#define CODEHERO_UI_STYLESHEET_H_ 

#include <memory>
#include <string>
#include "core/color.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Font;
class FontFace;

class Stylesheet {
public:
    struct Style {
        std::shared_ptr<Font> fontFamily;
        uint8_t fontSize;
        Color fontColor;
        Color backgroundColor;

        Color borderColor;

        // Cached
        std::shared_ptr<FontFace> defaultFontFace; // Combination Font + Size
    };

    explicit Stylesheet(const std::shared_ptr<EngineContext>& iContext);

    void _Initialize();

    // Global getters
    const Style& GetDefault() const {
        return m_Default;
    }

    const Style& GetHover() const {
        return m_Hover;
    }

    const Style& GetActive() const {
        return m_Active;
    }

private:
    std::shared_ptr<EngineContext> m_pContext;

    // Those are the three style categories supported
    // Those are very similar by default. The different will be only in colors
    Style m_Default;
    Style m_Hover;
    Style m_Active;
};

} // namespace CodeHero

#endif // CODEHERO_UI_STYLESHEET_H_
