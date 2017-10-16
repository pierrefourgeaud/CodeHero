// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/plane.h"
#include "graphics/rendersystem.h"
#include "graphics/vertexbuffer.h"

namespace CodeHero {

Plane::Plane(const std::shared_ptr<EngineContext>& iContext)
    : Mesh(iContext) {
    float vertices[] = {
        // Positions        // Normals         // Texture Coords
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f
    };

    std::shared_ptr<VertexBuffer> buffer(iContext->GetSubsystem<RenderSystem>()->CreateVertexBuffer());
    buffer->SetData(vertices, 6, VertexBuffer::MASK_Position | VertexBuffer::MASK_Normal | VertexBuffer::MASK_TexCoord);
    buffer->Unuse();

    AddVertexBuffer(buffer);
}

Plane::~Plane() {
}

} // namespace CodeHero

