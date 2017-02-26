// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_UIELEMENT_H_
#define CODEHERO_UI_UIELEMENT_H_ 

#include <vector>
#include "core/math/vector2.h"
#include "ui/uibatch.h"

namespace CodeHero {

// Forward declaration
class EngineContext;

class UIElement {
public:
    explicit UIElement(std::shared_ptr<EngineContext>& iContext);
    virtual ~UIElement() {}
    void AddChild(std::shared_ptr<UIElement> iElement);

    virtual void GetBatches(std::vector<UIBatch>& oBatches) {
        (void)oBatches;
    }

    const std::vector<std::shared_ptr<UIElement>>& GetChildren() { return m_Elements; }

    void SetPosition(const Vector2& iPos);
    void SetPosition(float iWidth, float iHeight);

protected:
    std::shared_ptr<EngineContext> m_pContext;
    Vector2 m_Position;

private:
    std::vector<std::shared_ptr<UIElement>> m_Elements;
};

} // namespace CodeHero

#endif // CODEHERO_UI_UIELEMENT_H_
