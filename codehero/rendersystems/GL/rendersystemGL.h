// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_RENDERSYSTEMGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_RENDERSYSTEMGL_H_

#include "./core/errors.h"
#include "./core/rendersystem.h"

namespace CodeHero {

// Forward declaration
class TextureManager;
class RenderWindow;
class Texture;

class RenderSystemGL : public RenderSystem {
public:
    virtual ~RenderSystemGL() {}

    Error Initialize() override;
    void PollEvents() override;
    Error Cleanup() override;

    void ClearFrameBuffer() override;

    // Factory
    RenderWindow* CreateWindow() final override;
    Texture* CreateTexture() final override;
    Shader* CreateShader() final override;
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_RENDERSYSTEMGL_H_
