// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/ui.h"
#include <queue>
#include "core/enginecontext.h"
#include "graphics/indexbuffer.h"
#include "graphics/rendersystem.h"
#include "graphics/vertexbuffer.h"
#include "ui/stylesheet.h"
#include "ui/uidraw.h"

namespace CodeHero {

UI::UI(std::shared_ptr<EngineContext>& iContext)
    : m_pContext(iContext)
    , m_RootElement(new UIElement(iContext)) {
    UIDraw::Init();
    m_RootElement->SetStyle(std::make_shared<Stylesheet>(m_pContext));
}

void UI::Update() {
    m_Batches.clear();
    _GetBatches(m_RootElement);
}

void UI::Render() {
    static std::shared_ptr<Texture> nullTexture = nullptr;
    RenderSystem* rs = m_pContext->GetSubsystem<RenderSystem>();

    // TODO(pierre) Should be moved somewhere more appropriate
    if (!nullTexture) {
        nullTexture = rs->CreateTexture();
        auto img = std::make_shared<Image>(m_pContext);
        img->Create(1, 1, { 255 }, Image::Format::IFMT_Grayscale);
        nullTexture->Load(img);
    }

    size_t size = m_Batches.size();
    for (size_t i = 0; i < size; ++i) {
        UIBatch& batch = m_Batches[i];
        batch.GetVertexBuffer()->Use();
        auto texture = batch.GetTexture();
        if (texture) {
            rs->SetTexture(0, *texture);
        } else {
            rs->SetTexture(0, *nullTexture);
        }
        auto indices = batch.GetIndexBuffer();
        if (indices) {
            indices->Use();
            rs->Draw(PT_Triangles, indices->GetSize());
        } else {
            rs->Draw(PT_Triangles, batch.GetStart(), batch.GetCount());
        }
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
        _GetBatches(children[i]);
        children[i]->GetBatches(m_Batches);
    }
}

} // namespace CodeHero

