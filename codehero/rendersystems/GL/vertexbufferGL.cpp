// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <glad/glad.h>
#include "rendersystems/GL/vertexbufferGL.h"

namespace CodeHero {

const uint8_t VertexBufferGL::ElementSize[] = {
    3 * sizeof(GL_FLOAT), // Position
    3 * sizeof(GL_FLOAT), // Normal
    4 * sizeof(GL_UNSIGNED_BYTE), // Color
    2 * sizeof(GL_FLOAT) // TexCoord
};

const uint32_t VertexBufferGL::ElementType[] = {
    GL_FLOAT, // Position
    GL_FLOAT, // Normal
    GL_UNSIGNED_BYTE, // Color
    GL_FLOAT // TexCoord
};

const uint32_t VertexBufferGL::ElementComponents[] = {
    3, // Position
    3, // Normal
    4, // Color
    2, // TexCoord
};

VertexBufferGL::VertexBufferGL() {
    glGenBuffers(1, &_GetGPUObjectHandle()->intHandle);
}

VertexBufferGL::~VertexBufferGL() {
    glDeleteBuffers(1, &_GetGPUObjectHandle()->intHandle);
}

void VertexBufferGL::_SetDataImpl() {
    glBindBuffer(GL_ARRAY_BUFFER, GetGPUObject().intHandle);
    glBufferData(
        GL_ARRAY_BUFFER,
        m_VertexCount * m_VertexSize,
        m_Data.get(),
        m_IsDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void VertexBufferGL::_SetSubDataImpl(uint32_t iStart, uint32_t iSize, const void* iData) {
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

}  // namespace CodeHero
