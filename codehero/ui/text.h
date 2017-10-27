// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_TEXT_H_
#define CODEHERO_UI_TEXT_H_ 

#include <memory>
#include <string>
#include "core/color.h"
#include "ui/uielement.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Font;
class UIBatch;

class Text : public UIElement {
public:
    explicit Text(std::shared_ptr<EngineContext>& iContext);

    void SetFont(const std::string& iFontName);
    void SetFont(std::shared_ptr<Font> iFont);
    void SetSize(uint32_t iSize);
    void SetText(const std::string& iText);
    void SetColor(const Color& iColor);

    void GetBatches(std::vector<UIBatch>& oBatches) override;

private:
    std::string m_Text;
    uint32_t m_Size;
    std::shared_ptr<Font> m_pFont;
    Color m_Color;
};

} // namespace CodeHero

#endif // CODEHERO_UI_TEXT_H_
