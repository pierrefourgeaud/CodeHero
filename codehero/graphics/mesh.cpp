// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/mesh.h"
#include "graphics/indexbuffer.h"
#include "graphics/vertexbuffer.h"
#include "graphics/rendersystem.h"

namespace CodeHero {

Mesh::Mesh() {}
Mesh::~Mesh() {}

void Mesh::Draw(RenderSystem* iRS) const {
    m_pVertices->Use();

    if (m_pIndices && m_pIndices->GetSize() > 0) {
        m_pIndices->Use();
        iRS->Draw(PT_Triangles, m_pIndices->GetSize());
    } else {
        iRS->Draw(PT_Triangles, 0, m_pVertices->GetVertexCount());
    }
}

void Mesh::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& iBuffer) {
    m_pVertices = iBuffer;
}

void Mesh::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer) {
    m_pIndices = iBuffer;
}

void Mesh::SetMaterial(const std::shared_ptr<Material> iMaterial) {
    m_pMaterial = iMaterial;
}

} // namespace CodeHero