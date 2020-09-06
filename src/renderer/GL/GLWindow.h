// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <memory>

#include "renderer/Window.h"

namespace CodeHero {

// Forward declaration
class IPlatformWindow;
class IGLContext;

class GLWindow : public Window {
 public:
    GLWindow();
    ~GLWindow() override;

    bool Create(uint32_t iWidth, uint32_t iHeight) override;
    void MakeContextCurrent() override;
    bool ShouldClose() const override;
    void SwapBuffers() override;

 private:
    std::unique_ptr<IPlatformWindow> m_pWindow;
    std::unique_ptr<IGLContext> m_pContext;
};

} // namespace CodeHero