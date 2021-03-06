// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/plane.h"
#include "core/type_traits/objectdefinition.h"
#include "graphics/rendersystem.h"
#include "graphics/vertexbuffer.h"

namespace CodeHero {

Plane::Plane(const std::shared_ptr<EngineContext>& iContext) : Mesh(iContext) {
    // clang-format off
    float vertices[] = {// Positions        // Normals         // Texture Coords
                        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
                         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
                        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f};
    // clang-format on

    std::shared_ptr<VertexBuffer> buffer(
        iContext->GetSubsystem<RenderSystem>()->CreateVertexBuffer());
    buffer->SetData(
        vertices, 6,
        VertexBuffer::MASK_Position | VertexBuffer::MASK_Normal | VertexBuffer::MASK_TexCoord);
    buffer->Unuse();

    AddVertexBuffer(buffer);
}

Plane::~Plane() {}

void Plane::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Plane);
}

std::shared_ptr<Plane> Plane::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Plane>(iContext);
}

} // namespace CodeHero
