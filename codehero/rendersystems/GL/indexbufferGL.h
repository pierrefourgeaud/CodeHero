// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_INDEXBUFFERGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_INDEXBUFFERGL_H_

#include "graphics/indexbuffer.h"

namespace CodeHero {

class IndexBufferGL : public IndexBuffer {
   public:
    IndexBufferGL();
    ~IndexBufferGL();

    void Use() override;
    void Unuse() override;

   protected:
    void _SetDataImpl(const void* iData) override;
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_INDEXBUFFERGL_H_
