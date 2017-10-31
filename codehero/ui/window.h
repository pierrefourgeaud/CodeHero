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
    enum Flags {
        F_NoHeader = 0
    };

    explicit Window(std::shared_ptr<EngineContext>& iContext);

    void SetFlags(Flags iFlags) { m_Flags = iFlags; }
    void SetHeader(const std::string& iText);

    void SetSize(const Vector2& iSize);
    const Vector2& GetSize() const;

    void GetBatches(std::vector<UIBatch>& oBatches) override;

    Vector2 GetLayoutPosition() const override;

private:
    Vector2 m_Size;
    std::string m_HeaderText;
    Flags m_Flags;
};

} // namespace CodeHero

#endif // CODEHERO_UI_WINDOW_H_
