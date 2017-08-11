// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_RENDERWINDOWGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_RENDERWINDOWGL_H_

#include "core/errors.h"
#include "graphics/renderwindow.h"

// Forward declaration
struct GLFWwindow;

namespace CodeHero {

class RenderWindowGL : public RenderWindow {
public:
    explicit RenderWindowGL(RenderSystem& iRenderSystem);
    virtual ~RenderWindowGL() {}

    Error Create(const int iWidth, const int iHeight) override;

    void SetShouldClose(bool iShouldClose) override;

    // If Grabbed is true (and with not visible), the mouse is grabbed and cannot
    // leave the client area
    void SetMouseVisible(bool iIsVisible, bool iGrabbed = true) override;
    bool ShouldClose() const override;
    void SwapBuffers() override;

private:
    GLFWwindow* m_pWindow = nullptr;

    static void _HandleKey(GLFWwindow* iWindow, int32_t iKey, int32_t iScancode, int32_t iAction, int32_t iMode);
    static void _HandleMouse(GLFWwindow* iWindow, double iPosX, double iPosY);
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_RENDERWINDOWGL_H_
