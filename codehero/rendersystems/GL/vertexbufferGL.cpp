// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "rendersystems/GL/vertexbufferGL.h"

#include "rendersystems/GL/vertexattribbinding.h"

#include <glad/glad.h>

namespace CodeHero {

const uint8_t VertexBufferGL::ElementSize[] = {
    3 * sizeof(GL_FLOAT), // Position
    3 * sizeof(GL_FLOAT), // Normal
    4 * sizeof(GL_FLOAT), // Color
    2 * sizeof(GL_FLOAT), // TexCoord,
    3 * sizeof(GL_FLOAT), // Tangent
    3 * sizeof(GL_FLOAT)  // Bitangent
};

const uint32_t VertexBufferGL::ElementType[] = {
    GL_FLOAT, // Position
    GL_FLOAT, // Normal
    GL_FLOAT, // Color
    GL_FLOAT, // TexCoord
    GL_FLOAT, // Tangent
    GL_FLOAT  // Bitangent
};

const uint32_t VertexBufferGL::ElementComponents[] = {
    3, // Position
    3, // Normal
    4, // Color
    2, // TexCoord,
    3, // Tangent
    3  // Bitangent
};

VertexBufferGL::VertexBufferGL() : m_pVAO(new VertexAttribBindingGL) {
    glGenBuffers(1, &_GetGPUObjectHandle()->intHandle);
}

VertexBufferGL::~VertexBufferGL() {
    glDeleteBuffers(1, &_GetGPUObjectHandle()->intHandle);
}

// Not sure of that...
// To be used when drawing on dynamic drawing
// glVertexAttribXXX As to be done before that
void VertexBufferGL::Use() {
    m_pVAO->Bind();
}

// Same same
void VertexBufferGL::Unuse() {
    m_pVAO->Unbind();
}

uint32_t VertexBufferGL::GetComponentsNumber() const {
    uint32_t components = 0;
    for (uint8_t i = 0; i < VertexBuffer::EL_Max; ++i) {
        if (m_Masks & (1 << i)) {
            components += ElementComponents[i];
        }
    }
    return components;
}

void VertexBufferGL::_SetDataImpl() {
    m_pVAO->Bind();
    glBindBuffer(GL_ARRAY_BUFFER, GetGPUObject().intHandle);
    glBufferData(GL_ARRAY_BUFFER, m_VertexCount * m_VertexSize, m_Data.get(),
                 m_IsDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    m_pVAO->CreateBinding(*this);
}

void VertexBufferGL::_SetSubDataImpl(uint32_t iStart, uint32_t iSize, const void* iData) {
    m_pVAO->Bind();
    glBindBuffer(GL_ARRAY_BUFFER, GetGPUObject().intHandle);
    glBufferSubData(GL_ARRAY_BUFFER, iStart, iSize, iData);
}

void VertexBufferGL::_UpdateSizeImpl() {
    uint32_t offset = 0;
    for (uint8_t i = 0; i < VertexBuffer::EL_Max; ++i) {
        if (m_Masks & (1 << i)) {
            m_ElementOffset[i] = offset;
            offset += ElementSize[i];
        }
    }
    m_VertexSize = offset;
}

} // namespace CodeHero
