// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/RendererGL.h"

#include "core/logger/Logger.h"
#include "renderer/GL/WindowGL.h"

// GLFW/GLAD header should be included at the end to avoid macro redefinition
// conflict with Windows headers.
#include <glad/glad.h>
#include <glfw/glfw3.h>

#if defined(PLATFORM_WINDOWS)
#if defined(CreateWindow)
#undef CreateWindow
#endif
#endif

namespace CodeHero {

bool RendererGL::Initialize() {
    if (!glfwInit()) {
        LOGE << "Failed to initialize GLFW. Quitting.";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // TODO(pierre): The following line might be needed for OSX.
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    return true;
}

bool RendererGL::Cleanup() {
    glfwTerminate();
    return true;
}

void RendererGL::PollEvents() {
    glfwPollEvents();
}

void RendererGL::Draw() {
    LOGI << "RendererGL::Draw for the win.";
}

std::shared_ptr<Window> RendererGL::CreateWindow(uint32_t iWidth, uint32_t iHeight) {
    auto window = std::make_shared<WindowGL>();
    if (window->Create(iWidth, iHeight)) {
        return window;
    }

    return nullptr;
}

} // namespace CodeHero