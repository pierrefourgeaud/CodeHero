// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RENDERSYSTEM_H_
#define CODEHERO_CORE_RENDERSYSTEM_H_

#include "./core/errors.h"

namespace CodeHero {

// Forward declaration
class TextureManager;
class RenderWindow;

class RenderSystem {
public:
    virtual ~RenderSystem() {}

    virtual Error Initialize() = 0;
    virtual void PollEvents() = 0;
    virtual Error Cleanup() = 0;

    virtual RenderWindow* CreateWindow() = 0;

    virtual void ClearFrameBuffer() = 0;

protected:
    void _SetTextureManager(TextureManager* iTextureManager) { m_pTextureManager = iTextureManager; }

private:
    TextureManager* m_pTextureManager = nullptr;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_RENDERSYSTEM_H_
