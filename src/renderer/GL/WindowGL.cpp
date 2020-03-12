// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/WindowGL.h"

#include "core/String.h"
#include "core/logger/Logger.h"

// GLFW/GLAG header should be included at the end to avoid macro redefinition
// conflict with Windows headers.
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace CodeHero {

WindowGL::WindowGL() {
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

WindowGL::~WindowGL() = default;

bool WindowGL::Create(uint32_t iWidth, uint32_t iHeight) {
    m_pWindow = glfwCreateWindow(iWidth, iHeight, "CodeHero", nullptr, nullptr);
    if (m_pWindow == nullptr) {
        LOGE << "Failed to create GLFW window. Forcing to terminate GLFW.";
        glfwTerminate();
        return false;
    }

    MakeContextCurrent();

    // A context need to be current for this.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOGE << "Failed to initialize GLAD. Aborting all GL.";
        glfwTerminate();
        return false;
    }

    LOGI << "OpenGL version: " << CastANSIToString((const char*)glGetString(GL_VERSION));

    return true;
}

void WindowGL::MakeContextCurrent() {
    glfwMakeContextCurrent(m_pWindow);
}

bool WindowGL::ShouldClose() const {
    return glfwWindowShouldClose(m_pWindow);
}

void WindowGL::SwapBuffers() {
    glfwSwapBuffers(m_pWindow);
}

} // namespace CodeHero