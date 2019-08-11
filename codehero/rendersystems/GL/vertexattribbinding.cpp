// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "rendersystems/GL/vertexattribbinding.h"

#include "rendersystems/GL/utils.h"
#include "rendersystems/GL/vertexbufferGL.h"

#include <glad/glad.h>

namespace CodeHero {

VertexAttribBindingGL::VertexAttribBindingGL() {
    CH_GL_CALL(glGenVertexArrays(1, &_GetGPUObjectHandle()->intHandle));
}

VertexAttribBindingGL::~VertexAttribBindingGL() {
    CH_GL_CALL(glDeleteVertexArrays(1, &_GetGPUObjectHandle()->intHandle));
}

void VertexAttribBindingGL::Bind() {
    CH_GL_CALL(glBindVertexArray(GetGPUObject().intHandle));
}

void VertexAttribBindingGL::Unbind() {
    CH_GL_CALL(glBindVertexArray(0));
}

void VertexAttribBindingGL::CreateBinding(const VertexBufferGL& iBuffer) {
    uint32_t vertexSize = iBuffer.GetVertexSize();

    for (uint32_t i = 0; i < VertexBuffer::EL_Max; ++i) {
        uint32_t bit = 1 << i;
        if (iBuffer.IsBitActive(bit)) {
            CH_GL_CALL(glVertexAttribPointer(
                i, VertexBufferGL::ElementComponents[i], VertexBufferGL::ElementType[i], GL_FALSE,
                vertexSize, reinterpret_cast<GLvoid*>(iBuffer.GetElementOffset(i))));
            CH_GL_CALL(glEnableVertexAttribArray(i));
        }
    }
}

} // namespace CodeHero
