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

#include "graphics/renderwindow.h"
#include "graphics/viewport.h"
#include "graphics/camera.h"

#include "ui/ui.h"

#include "rendersystems/GL/rendersystemGL.h"
#include "rendersystems/GL/textureGL.h"

#include "./core/math/vector3.h"
#include "./core/math/matrix4.h"

#include "graphics/vertexbuffer.h"

#include "ui/font.h"
#include "ui/fontface.h"

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

    UI ui(m_pRS);

    // Build and compile our shader program
    Shader* ourShader = m_pRS->CreateShader();
    ourShader->Attach("./codehero/shaders/textured.vert")
             .Attach("./codehero/shaders/textured.frag")
             .Link();

    Shader* textShader = m_pRS->CreateShader();
    textShader->Attach("./codehero/shaders/text_basic.vert")
              .Attach("./codehero/shaders/text_basic.frag")
              .Link();
    textShader->Use();
    OrthoMatrix ortho(0, 600, 0, 600);
    m_pRS->SetShaderParameter("projection", ortho);

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    VertexBuffer* buffer = m_pRS->CreateVertexBuffer();
    buffer->SetData(vertices, 36, VertexBuffer::MASK_Position | VertexBuffer::MASK_Normal | VertexBuffer::MASK_TexCoord);
    buffer->Unuse();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    Font f(*m_pRS, "./resources/fonts/Roboto-Regular.ttf");
    std::shared_ptr<FontFace> fa = f.GetFace(24);

    VertexBuffer* buffer2 = m_pRS->CreateVertexBuffer();
    buffer2->SetData(nullptr, 6, VertexBuffer::MASK_Position | VertexBuffer::MASK_TexCoord, true);
    buffer2->Unuse();

    // Load and create a texture
    Texture* texture1 = m_pRS->CreateTexture();
    texture1->Load("./resources/images/container2.png");

    Texture* texture2 = m_pRS->CreateTexture();
    texture2->Load("./resources/images/container2_specular.png");

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
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    int fps = 0.0;
    // double mspf = 0.0;
    Viewport* viewportMain = new Viewport(0, 0, 600, 600);
    Viewport* viewportTopRight = new Viewport(600, 400, 200, 200);
    Viewport* viewportMiddleRight = new Viewport(600, 200, 200, 200);
    Viewport* viewportBottomRight = new Viewport(600, 0, 200, 200);

    Vector3 pointLightPositions[] = {
        { 0.7f,  0.2f,  2.0f},
        { 2.3f, -3.3f, -4.0f},
        {-4.0f,  2.0f, -12.0f},
        { 0.0f,  0.0f, -3.0f}
    };

    Camera camera({0.0f, 2.2f, 3.5f}, {0.0f, 1.0f, 0.0f});

    while (!m_pMainWindow->ShouldClose()) {
        m_pRS->PollEvents();

        m_pRS->ClearFrameBuffer();
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            fps = nbFrames;
            // printf("%f ms/frame\n", 1000.0/double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        // ###################################################
        float scale = 1.0f;
        float x = 10.0f;
        float y = 565.0f;
        std::string text("FPS: " + std::to_string(fps));
        Vector3 color(0.5, 0.8f, 0.2f);
        textShader->Use();
        m_pRS->SetShaderParameter("textColor", color);
        glActiveTexture(GL_TEXTURE0);
        buffer2->Use();

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            FontFaceGlyph& ch = fa->GetGlyph(*c);

            float xpos = x + ch.left * scale;
            float ypos = y - (ch.height - ch.top) * scale;

            float w = ch.width * scale;
            float h = ch.height * scale;
            // Update VBO for each character
            float vertices[6][5] = {
                { xpos,     ypos + h, 0.0, 0.0, 0.0 },
                { xpos,     ypos,     0.0, 0.0, 1.0 },
                { xpos + w, ypos,     0.0, 1.0, 1.0 },

                { xpos,     ypos + h, 0.0, 0.0, 0.0 },
                { xpos + w, ypos,     0.0, 1.0, 1.0 },
                { xpos + w, ypos + h, 0.0, 1.0, 0.0 }
            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.texture->GetGPUObject().intHandle);
            buffer2->SetSubData(vertices, 0, 6);

            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advanceX >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        buffer2->Unuse();
        glBindTexture(GL_TEXTURE_2D, 0);
        // ###################################################

        // Draw the triangle
        ourShader->Use();

        // Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetGPUObject().intHandle);
        glUniform1i(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "material.diffuse"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetGPUObject().intHandle);
        glUniform1i(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "material.specular"), 1);

        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "material.shininess"), 32.0f);

        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "dirLight[0].direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "dirLight[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "dirLight[0].diffuse"), 0.4f, 0.4f, 0.4f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "dirLight[0].specular"), 0.5f, 0.5f, 0.5f);
        // Point light 1
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[0].position"), 0.7f, 0.2f, 2.0f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[0].linear"), 0.09);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[0].quadratic"), 0.032);

        // Point light 2
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[1].position"), pointLightPositions[1].x(), pointLightPositions[1].y(), pointLightPositions[1].z());
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[1].linear"), 0.09);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[1].quadratic"), 0.032);
        // Point light 3
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[2].position"), pointLightPositions[2].x(), pointLightPositions[2].y(), pointLightPositions[2].z());
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[2].linear"), 0.09);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[2].quadratic"), 0.032);
        // Point light 4
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[3].position"), pointLightPositions[3].x(), pointLightPositions[3].y(), pointLightPositions[3].z());
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[3].linear"), 0.09);
        glUniform1f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[3].quadratic"), 0.032);

        PerspectiveMatrix projection(45.0f, 800 / 600, 0.1f, 100.0f);

        m_pRS->SetShaderParameter("view", camera.GetView());
        m_pRS->SetShaderParameter("projection", projection);

        // Draw container
        buffer->Use();
        for (GLuint i = 0; i < 10; ++i) {
            Matrix4 model;
            model.Translate(cubePositions[i]);
            model.Rotate(glfwGetTime() * 20.0f * i, {1.0f, 0.3f, 0.5f});

            m_pRS->SetShaderParameter("model", model);
            m_pRS->SetViewport(viewportMiddleRight);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_pRS->SetViewport(viewportBottomRight);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_pRS->SetViewport(viewportTopRight);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_pRS->SetViewport(viewportMain);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        buffer->Unuse();

        m_pMainWindow->SwapBuffers();
    }

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
#endif // DRIVER_PNG
    LOGI << "Drivers loaded..." << std::endl;
}

void Main::_UnloadDrivers() {
    LOGI << "Unloading drivers..." << std::endl;
    m_ImageLoader.ClearCodecs();
    LOGI << "Drivers unloaded..." << std::endl;
}

} // namespace CodeHero
