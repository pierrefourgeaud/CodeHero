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
class Stylesheet;

class UIElement : public std::enable_shared_from_this<UIElement> {
public:
    explicit UIElement(std::shared_ptr<EngineContext>& iContext);
    virtual ~UIElement() {}

    void AddChild(std::shared_ptr<UIElement> iElement);
    void SetParent(const std::shared_ptr<UIElement>& iParent);
    const std::shared_ptr<UIElement>& GetParent() const { return m_pParent; }

    bool IsRoot() const { return m_pParent == nullptr; }

    void SetStyle(const std::shared_ptr<Stylesheet>& iStyle) {
        m_pStyle = iStyle;
    }

    const std::shared_ptr<Stylesheet>& GetStyle() const {
        return m_pStyle;
    }

    virtual void GetBatches(std::vector<UIBatch>& oBatches) {
        (void)oBatches;
    }

    const std::vector<std::shared_ptr<UIElement>>& GetChildren() { return m_Elements; }

    void SetPosition(const Vector2& iPos);
    void SetPosition(float iWidth, float iHeight);
    const Vector2& GetPosition() const { return m_Position; }
    // This method can be overriden. Most elements will not need to
    // but certain element might have a different layout position
    // from the element position (i.e. Window that have a header)
    virtual Vector2 GetLayoutPosition() const { return m_Position; }

protected:
    std::shared_ptr<EngineContext> m_pContext;
    Vector2 m_Position;

    std::shared_ptr<Stylesheet> m_pStyle;

private:
    std::shared_ptr<UIElement> m_pParent;
    std::vector<std::shared_ptr<UIElement>> m_Elements;
};

} // namespace CodeHero

#endif // CODEHERO_UI_UIELEMENT_H_
