// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_VERTEXATTRIBBINDINGGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_VERTEXATTRIBBINDINGGL_H_

#include "core/gpuobject.h"

namespace CodeHero {

// Forward declaration
class VertexBufferGL;

class VertexAttribBindingGL : public GPUObject {
public:
    VertexAttribBindingGL();
    ~VertexAttribBindingGL();

    void Bind();
    void Unbind();

    void CreateBinding(const VertexBufferGL& iBuffer);
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_VERTEXATTRIBBINDINGGL_H_
