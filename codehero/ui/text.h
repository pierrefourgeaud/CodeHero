// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_TEXT_H_
#define CODEHERO_UI_TEXT_H_ 

#include "ui/uielement.h"
#include <memory>
#include <string>
#include <graphics/rendersystem.h>

namespace CodeHero {

// Forward declaration
class Font;
class UIBatch;

class Text : public UIElement {
public:
    explicit Text(std::shared_ptr<RenderSystem> iRS);

    void SetFont(const std::string& iFontName);
    void SetFont(std::shared_ptr<Font> iFont);
    void SetSize(uint32_t iSize);
    void SetText(const std::string& iText);

    void GetBatches(std::vector<UIBatch>& oBatches) override;

private:
    std::string m_Text;
    uint32_t m_Size;
    std::shared_ptr<Font> m_pFont;
};

} // namespace CodeHero

#endif // CODEHERO_UI_TEXT_H_
