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
    m_Vertices.push_back(iBuffer);
}

void Mesh::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer) {
    m_Indices.push_back(iBuffer);
}


} // namespace CodeHero

