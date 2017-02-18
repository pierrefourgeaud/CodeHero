// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/ui.h"
#include <queue>
#include "graphics/rendersystem.h"
#include "graphics/vertexbuffer.h"

namespace CodeHero {

UI::UI(std::shared_ptr<RenderSystem> iRS)
    : m_pRS(iRS)
    , m_RootElement(new UIElement(m_pRS)) {}

void UI::Update() {
    m_Batches.clear();
    _GetBatches(m_RootElement);
}

void UI::Render() {
    size_t size = m_Batches.size();
    for (size_t i = 0; i < size; ++i) {
        UIBatch& batch = m_Batches[i];
        batch.GetVertexBuffer()->Use();
        m_pRS->SetTexture(0, *batch.GetTexture());
        m_pRS->Draw(PT_Triangles, batch.GetStart(), batch.GetCount());
        batch.GetVertexBuffer()->Unuse();
    }
}

void UI::AddChild(std::shared_ptr<UIElement> iElement) {
    m_RootElement->AddChild(iElement);
}

// IS DFS traversal ok ?
void UI::_GetBatches(std::shared_ptr<UIElement> iElement) {
    const std::vector<std::shared_ptr<UIElement>>& children = iElement->GetChildren();

    size_t size = children.size();

    // Going through the UI tree using a DFS algorithm
    for (size_t i = 0; i < size; ++i) {
        children[i]->GetBatches(m_Batches);
        _GetBatches(children[i]);
    }
}

} // namespace CodeHero

