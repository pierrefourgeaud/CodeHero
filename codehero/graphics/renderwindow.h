// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RENDERWINDOW_H_
#define CODEHERO_CORE_RENDERWINDOW_H_

#include <memory>
#include "core/errors.h"

namespace CodeHero {

// Forward declaration
class RenderSystem;
class Input;

class RenderWindow {
public:
    explicit RenderWindow(RenderSystem& iRenderSystem) : m_rRenderSystem(iRenderSystem) {}
    virtual ~RenderWindow() {}

    virtual Error Create(int iWidth, int iHeight) = 0;
    virtual void SetShouldClose(bool iShouldClose) = 0;

    virtual void SetMouseVisible(bool iIsVisible, bool iGrabbed = true) = 0;
    virtual bool ShouldClose() const = 0;
    virtual void SwapBuffers() = 0;

    // TODO(pierre) Should be changed to either reference or shared_ptr !
    void SetInputHandler(Input* iInputHandler) { m_pInputHandler = iInputHandler; }

protected:
    RenderSystem& m_rRenderSystem;
    Input* m_pInputHandler;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_RENDERWINDOW_H_
