// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

// TODO(pierre) to remove
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>

#include "./main.h"
#include <logger.h>
#include <filelogger.h>
#include <consolelogger.h>

#include "./core/shader.h"
#include "./core/imageloader.h"
#include "./core/image.h"

#include "./core/renderwindow.h"
#include "./rendersystems/GL/rendersystemGL.h"
#include "./rendersystems/GL/textureGL.h"

#include "./core/math/vector3.h"
#include "./core/math/matrix4.h"

#ifdef DRIVER_PNG
# include "./drivers/png/imagecodec_png.h"
#endif  // DRIVER_PNG

namespace CodeHero {

Main::Main()
    : m_ImageLoader(*ImageLoader::GetInstance()) {
    _Initialize();
}

Main::~Main() {
    _Cleanup();
}

Error Main::Start() {
    LOGD2 << "[>] Main::Start()" << std::endl;

    m_pRS.reset(new RenderSystemGL);
    Error error = m_pRS->Initialize();

    if (!error) {
        m_pMainWindow.reset(m_pRS->CreateWindow());
    }

    LOGD2 << "[<] Main::Start()" << std::endl;

    return error;
}

Error Main::Run() {
    LOGD2 << "[>] Main::Run()" << std::endl;

    // TODO TUTO

    // Build and compile our shader program
    Shader ourShader;
    ourShader.Attach("./codehero/shaders/cs_basic.vert")
             .Attach("./codehero/shaders/shader_basic_trans.frag")
             .Link();

    Vector3 vec(0, 0, 0);
    vec.Length();

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

//    GLuint indices[] = {  // Note that we start from 0!
//        0, 1, 3, // First Triangle
//        1, 2, 3  // Second Triangle
//    };
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    // Load and create a texture
    Texture* texture1 = new TextureGL;
    texture1->Load("/Users/pierrefourgeaud/Documents/container.png");

    Texture* texture2 = new TextureGL;
    texture2->Load("/Users/pierrefourgeaud/Documents/awesomeface.png");

    Vector3 cubePositions[] = {
        { 0.0f,  0.0f,  0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        { 1.3f, -2.0f, -2.5f},
        { 1.5f,  2.0f, -2.5f},
        { 1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
    };

    auto start = std::chrono::system_clock::now();

    while (!m_pMainWindow->ShouldClose()) {
        m_pRS->PollEvents();

        m_pRS->ClearFrameBuffer();

        // TODO(pierre) TUTO
        // Draw the triangle
        ourShader.Use();

        // Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, static_cast<TextureGL*>(texture1)->GetGLID());
        glUniform1i(glGetUniformLocation(ourShader.Get(), "ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, static_cast<TextureGL*>(texture2)->GetGLID());
        glUniform1i(glGetUniformLocation(ourShader.Get(), "ourTexture2"), 1);

//        auto end = std::chrono::system_clock::now();
//
//        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//        float tr;
//        if (diff.count() < 2500) {
//            tr = -1.0f + (float)diff.count() / 1250.0f;
//        } else if (diff.count() < 5000) {
//            tr = 1.0f - ((float)diff.count() - 2500.0f) / 1250.0f;
//        } else {
//            start = end;
//        }
//
//        Matrix4 transform;
//        transform.Translate({tr, -tr, 0.0f});
//        transform.Rotate((GLfloat)glfwGetTime() * 50.0f, {0.0f, 0.0f, 1.0f});

//        model = glm::rotate(model, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.5f, 1.0f, 0.0f));

        Matrix4 view;
        view.Translate({0.0f, 0.0f, -3.0f});

        PerspectiveMatrix projection(45.0f, 800 / 600, 0.1f, 100.0f);

        GLint transformLoc = glGetUniformLocation(ourShader.Get(), "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Get(), "view");
        GLint projectionLoc = glGetUniformLocation(ourShader.Get(), "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.GetPtr());
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.GetPtr());

        // Draw container
        glBindVertexArray(VAO);
        for(GLuint i = 0; i < 10; ++i) {
            Matrix4 model;
            model.Translate(cubePositions[i]);
            model.Rotate(glfwGetTime() * 20.0f * i, {1.0f, 0.3f, 0.5f});

            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, model.GetPtr());
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        m_pMainWindow->SwapBuffers();
    }

    // TODO TUTO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);

    LOGD2 << "[<] Main::Run()" << std::endl;
    return Error::OK;
}

void Main::_Initialize() {
    SimpleLogger::ReportingLevel() = ELogLevel::Debug2;

    m_pFileLogger.reset(new FileLogger());
    SimpleLogger::AddListener(m_pFileLogger.get());

    m_pConsoleLogger.reset(new ConsoleLogger());
    SimpleLogger::AddListener(m_pConsoleLogger.get());

    LOGD2 << "[>] Main::_Initialize()" << std::endl;

    _LoadDrivers();
    LOGD2 << "[<] Main::_Initialize()" << std::endl;
}

void Main::_Cleanup() {
    m_pRS->Cleanup();

    _UnloadDrivers();
}

void Main::_LoadDrivers() {
    LOGI << "Loading drivers..." << std::endl;
#ifdef DRIVER_PNG
    m_ImageLoader.AddCodec(new ImageCodecPNG());
#endif  // DRIVER_PNG
    LOGI << "Drivers loaded..." << std::endl;
}

void Main::_UnloadDrivers() {
    LOGI << "Unloading drivers..." << std::endl;
    m_ImageLoader.ClearCodecs();
    LOGI << "Drivers unloaded..." << std::endl;
}

}  // namespace CodeHero
