// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./main.h"
#include "../core/logging/logger.h"
#include "../core/logging/filelogger.h"

namespace CodeHero {

Main::Main() {
    _Initialize();
}

Main::~Main() {
    _Cleanup();
}

Error Main::Start() {
    m_pFileLogger = new FileLogger();
    Logger::AddListener(m_pFileLogger);

    Logger::ReportingLevel() = ELogLevel::Debug;

    m_pWindow = glfwCreateWindow(800, 600, "CodeHero", nullptr, nullptr);

    // Check for Valid Context
    if (m_pWindow == nullptr) {
        return Error::ERR_CANT_CREATE;
    }

    glfwMakeContextCurrent(m_pWindow);
    gladLoadGL();

    return Error::OK;
}

Error Main::Run() {
    while (!glfwWindowShouldClose(m_pWindow)) {
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

    return Error::OK;
}

void Main::_Initialize() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void Main::_Cleanup() {
    if (m_pFileLogger) { delete m_pFileLogger; }

    glfwTerminate();
}

}  // namespace CodeHero
