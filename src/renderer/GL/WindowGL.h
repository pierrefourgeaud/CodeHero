// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "renderer/Window.h"

// Forward declaration
struct GLFWwindow;

namespace CodeHero {

class WindowGL : public Window {
 public:
    WindowGL();
    ~WindowGL() override;

    bool Create(uint32_t iWidth, uint32_t iHeight) override;
    void MakeContextCurrent() override;
    bool ShouldClose() const override;
    void SwapBuffers() override;

 private:
    GLFWwindow* m_pWindow = nullptr;
};

} // namespace CodeHero