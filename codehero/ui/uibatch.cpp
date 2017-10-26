// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/uibatch.h"
#include "graphics/vertexbuffer.h"

namespace CodeHero {

void UIBatch::SetTexture(std::shared_ptr<Texture> iTexture) {
    m_pTexture = iTexture;
}

void UIBatch::SetVertexBuffer(
    std::shared_ptr<VertexBuffer> iVertexBuffer,
    uint32_t iStart/* = 0*/,
    uint32_t iCount/* = 0*/) {
    m_Start = iStart;
    m_Count = iCount == 0 ? iVertexBuffer->GetVertexSize() : iCount;
    m_pVertexBuffer = iVertexBuffer;
}

void UIBatch::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& iIndexBuffer) {
    m_pIndexBuffer = iIndexBuffer;
}

} // namespace CodeHero

