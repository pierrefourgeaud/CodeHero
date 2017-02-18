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
class RenderSystem;
class UIBatch;

class UI {
public:
    explicit UI(std::shared_ptr<RenderSystem> iRS);

    void Update();
    void Render();
    void AddChild();

private:
    std::shared_ptr<RenderSystem> m_pRS;

    UIElement m_RootElement;
    // Batches to render
    std::vector<UIBatch> m_Batches;
};

} // namespace CodeHero

#endif // CODEHERO_UI_UI_H_
