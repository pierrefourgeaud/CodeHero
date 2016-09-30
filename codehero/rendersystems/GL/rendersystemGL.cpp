// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <logger.h>
#include "./rendersystems/GL/rendersystemGL.h"
#include "./rendersystems/GL/renderwindowGL.h"
#include "./rendersystems/GL/texturemanagerGL.h"

namespace CodeHero {

Error RenderSystemGL::Initialize() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    return Error::OK;
}

void RenderSystemGL::PollEvents() {
    glfwPollEvents();
}

Error RenderSystemGL::Cleanup() {
    glfwTerminate();
    return Error::OK;
}

RenderWindow* RenderSystemGL::CreateWindow() {
    RenderWindow* win = new RenderWindowGL();
    if (win->Create(800, 600) != Error::OK) {
        delete win;
        win = nullptr;
    }

    LOGI << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return win;
}

void RenderSystemGL::ClearFrameBuffer() {
    // Background Fill Color
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // CodeHero
