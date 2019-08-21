// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_TEXTUREMANAGERGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_TEXTUREMANAGERGL_H_

#include "./core/errors.h"
#include "./core/texturemanager.h"

namespace CodeHero {

// Forward declaration
class TextureManager;

class TextureManagerGL : public TextureManager {
public:
    virtual ~TextureManagerGL() {}
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_TEXTUREMANAGERGL_H_
