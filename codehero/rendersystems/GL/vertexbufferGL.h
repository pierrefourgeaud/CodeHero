// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_VERTEXBUFFERGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_VERTEXBUFFERGL_H_

#include "graphics/vertexbuffer.h"

namespace CodeHero {

class VertexBufferGL : public VertexBuffer {
public:
    VertexBufferGL();
    ~VertexBufferGL();

    static const uint8_t ElementSize[];
    static const uint32_t ElementType[];
    static const uint32_t ElementComponents[];

protected:
    void _SetDataImpl() final override;
    void _SetSubDataImpl(uint32_t iStart, uint32_t iSize, const void* iData) final override;
    void _UpdateSizeImpl() final override;
};

}  // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_VERTEXBUFFERGL_H_
