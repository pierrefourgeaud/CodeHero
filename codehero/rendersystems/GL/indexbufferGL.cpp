// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "rendersystems/GL/indexbufferGL.h"
#include <glad/glad.h>

namespace CodeHero {

IndexBufferGL::IndexBufferGL() {
    glGenBuffers(1, &_GetGPUObjectHandle()->intHandle);
}

IndexBufferGL::~IndexBufferGL() {
    glDeleteBuffers(1, &_GetGPUObjectHandle()->intHandle);
}

void IndexBufferGL::Use() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GetGPUObject().intHandle);
}

void IndexBufferGL::Unuse() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferGL::_SetDataImpl(const void* iData) {
    Use();

    // TODO(pierre) The sizeof should be more abstracted
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexSize * sizeof(unsigned int), iData,
                 m_IsDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

} // namespace CodeHero
