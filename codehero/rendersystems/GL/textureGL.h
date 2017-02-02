// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_TEXTUREGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_TEXTUREGL_H_

#include <glad/glad.h>
#include "core/texture.h"

namespace CodeHero {

class TextureGL : public Texture {
public:
    TextureGL();
    ~TextureGL();

protected:
    bool _CreateImpl() override;

private:
    GLenum _GetGLFormat(const Image::Format iFormat);
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_TEXTUREGL_H_