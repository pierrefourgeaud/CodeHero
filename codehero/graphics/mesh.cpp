// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/mesh.h"
#include "graphics/indexbuffer.h"
#include "graphics/vertexbuffer.h"

namespace CodeHero {

Mesh::Mesh() {}
Mesh::~Mesh() {}

void Mesh::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& iBuffer) {
    m_Vertices = iBuffer;
}

void Mesh::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer) {
    m_Indices = iBuffer;
}

void Mesh::SetTextures(const TextureUnitsMaps& iTextures) {
    m_Textures = iTextures;
}

void Mesh::SetTexture(TextureUnit iUnit, const std::shared_ptr<Texture>& iTexture) {
    m_Textures[iUnit] = iTexture;
}

std::shared_ptr<Texture> Mesh::GetTexture(TextureUnit iUnit) const {
    auto texture = m_Textures.find(iUnit);
    if (texture == m_Textures.end()) {
        return nullptr;
    }

    return texture->second;
}


} // namespace CodeHero

