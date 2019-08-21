// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_BUTTON_H_
#define CODEHERO_UI_BUTTON_H_

#include <memory>
#include <string>
#include "core/color.h"
#include "core/math/vector2.h"
#include "ui/uielement.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Font;
class UIBatch;

class Button : public UIElement {
public:
    explicit Button(std::shared_ptr<EngineContext>& iContext);

    void SetText(const std::string& iText);

    void SetSize(const Vector2& iSize);
    const Vector2& GetSize() const;

    void GetBatches(std::vector<UIBatch>& oBatches) override;

private:
    Vector2 m_Size;
    std::string m_Text;
};

} // namespace CodeHero

#endif // CODEHERO_UI_BUTTON_H_
