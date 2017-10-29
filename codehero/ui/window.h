// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_WINDOW_H_
#define CODEHERO_UI_WINDOW_H_ 

#include "ui/uielement.h"
#include <memory>
#include <string>
#include "core/color.h"
#include "core/math/vector2.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Font;
class UIBatch;

class Window : public UIElement {
public:
    explicit Window(std::shared_ptr<EngineContext>& iContext);

    void SetHeader(const std::string& iText);

    void SetSize(const Vector2& iSize);
    const Vector2& GetSize() const;

    void SetNormalStrokeColor(const Color& iColor);
    void SetNormalBgColor(const Color& iColor);

    void GetBatches(std::vector<UIBatch>& oBatches) override;

private:
    Vector2 m_Size;
    std::string m_HeaderText;
    //std::shared_ptr<Font> m_pFont;

    // TODO(pierre) Should be refactored in objects like:
    // ObjectStyle m_Normal;
    // ObjectStyle m_Hover;
    // ObjectStyle m_Active;
    // With object Style having:
    // {
    //   Color color; // Text ?
    //   Color strokeColor;
    //   uint32 strokeSize;
    //   uint32 radius; // Could be 4 values for the 4 different corners
    //   Color backgroundColor;
    //   uint32_t fontSize; ?
    //   FontFact ????
    // }
    Color m_NormalBgColor;
    Color m_NormalStrokeColor;
};

} // namespace CodeHero

#endif // CODEHERO_UI_WINDOW_H_
