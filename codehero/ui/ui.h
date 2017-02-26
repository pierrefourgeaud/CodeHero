// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_UI_H_
#define CODEHERO_UI_UI_H_ 

#include <memory>
#include <vector>
#include "ui/uielement.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class UIBatch;

class UI {
public:
    explicit UI(std::shared_ptr<EngineContext>& iContext);

    void Update();
    void Render();
    void AddChild(std::shared_ptr<UIElement> iElement);

private:
    std::shared_ptr<EngineContext> m_pContext;

    std::shared_ptr<UIElement> m_RootElement;
    // Batches to render
    std::vector<UIBatch> m_Batches;

    void _GetBatches(std::shared_ptr<UIElement> iElement);
};

} // namespace CodeHero

#endif // CODEHERO_UI_UI_H_
