// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./main.h"
#include "../core/logging/logger.h"
#include "../core/logging/filelogger.h"
#include "../core/logging/bufferlogger.h"

namespace CodeHero {

Main::Main() {
    _Initialize();
}

Main::~Main() {
    _Cleanup();
}

Error Main::Start() {
    LOGD2 << "[>] Main::Start()" << std::endl;

    m_pWindow = glfwCreateWindow(800, 600, "CodeHero", nullptr, nullptr);

    // Check for Valid Context
    if (m_pWindow == nullptr) {
        return Error::ERR_CANT_CREATE;
    }

    glfwMakeContextCurrent(m_pWindow);
    gladLoadGL();

    LOGD2 << "[<] Main::Start()" << std::endl;

    return Error::OK;
}

Error Main::Run() {
    LOGD2 << "[>] Main::Run()" << std::endl;
    while (!glfwWindowShouldClose(m_pWindow)) {
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();

        if (m_pBufferLogger) {
            std::string str = static_cast<BufferLogger*>(m_pBufferLogger)->GetBuffer();
            if (!str.empty()) {
                std::cout << str << std::endl;
            }
        }
    }

    LOGD2 << "[<] Main::Run()" << std::endl;
    return Error::OK;
}

void Main::_Initialize() {
    Logger::ReportingLevel() = ELogLevel::Debug2;

    m_pFileLogger = new FileLogger();
    Logger::AddListener(m_pFileLogger);

    m_pBufferLogger = new BufferLogger();
    Logger::AddListener(m_pBufferLogger);

    LOGD2 << "[>] Main::_Initialize()" << std::endl;
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    LOGD2 << "[<] Main::_Initialize()" << std::endl;
}

void Main::_Cleanup() {
    if (m_pFileLogger)   { delete m_pFileLogger; }
    if (m_pBufferLogger) { delete m_pBufferLogger; }

    glfwTerminate();
}

}  // namespace CodeHero
