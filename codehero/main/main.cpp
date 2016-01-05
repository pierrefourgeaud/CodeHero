// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./main.h"
#include "../core/logging/logger.h"
#include "../core/logging/filelogger.h"
#include "../core/logging/bufferlogger.h"

#include "../core/shader.h"

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

    LOGI << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glViewport(0, 0, 800, 600);

    glfwSetKeyCallback(m_pWindow, Main::_HandleKey);

    LOGD2 << "[<] Main::Start()" << std::endl;

    return Error::OK;
}

Error Main::Run() {
    LOGD2 << "[>] Main::Run()" << std::endl;

    // TODO TUTO

    // Build and compile our shader program
    Shader ourShader;
    ourShader.Attach("./codehero/shaders/shader.vert")
             .Attach("./codehero/shaders/shader.frag")
             .Link();

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // Positions         // Colors
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
       -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO



    while (!glfwWindowShouldClose(m_pWindow)) {
        glfwPollEvents();

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO TUTO
        // Draw the triangle
        ourShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(m_pWindow);

        if (m_pBufferLogger) {
            std::string str = static_cast<BufferLogger*>(m_pBufferLogger)->GetBuffer();
            if (!str.empty()) {
                std::cout << str << std::endl;
            }
        }
    }

    // TODO TUTO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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

void Main::_HandleKey(GLFWwindow* iWindow, int32 iKey, int32 iScancode, int32 iAction, int32 iMode) {
    if (iKey == GLFW_KEY_ESCAPE && iAction == GLFW_PRESS) {
        glfwSetWindowShouldClose(iWindow, GL_TRUE);
    }
}

}  // namespace CodeHero
