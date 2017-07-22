// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

// TODO(pierre) to remove
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>

#include "main/main.h"
#include <logger.h>
#include <filelogger.h>
#include <consolelogger.h>

#include "core/enginecontext.h"

#include "core/shader.h"
#include "core/resourceloader.h"
#include "core/image.h"

#include "graphics/renderwindow.h"
#include "graphics/viewport.h"
#include "graphics/camera.h"
#include "graphics/model.h"

#include "ui/font.h"
#include "ui/ui.h"
#include "ui/text.h"

#include "rendersystems/GL/rendersystemGL.h"
#include "rendersystems/GL/textureGL.h"

#include "core/math/vector3.h"
#include "core/math/matrix4.h"

#include "graphics/vertexbuffer.h"

#ifdef DRIVER_PNG
# include "drivers/png/imagecodec_png.h"
#endif // DRIVER_PNG

#ifdef DRIVER_ASSIMP
# include "drivers/assimp/modelcodec_assimp.h"
#endif // DRIVER_ASSIMP

namespace CodeHero {

Main::Main() {
    _Initialize();
}

Main::~Main() {
    _Cleanup();
}

Error Main::Start() {
    LOGD2 << "[>] Main::Start()" << std::endl;

    // Create the context that will be the base of everything coming after
    m_pContext = std::shared_ptr<EngineContext>(new EngineContext);

    ResourceLoader<Image>* rlImage = new ResourceLoader<Image>(m_pContext);
    rlImage->Initialize();
    m_pContext->RegisterSubsystem(rlImage);

    ResourceLoader<Model>* rlModel = new ResourceLoader<Model>(m_pContext);
    rlModel->Initialize();
    m_pContext->RegisterSubsystem(rlModel);

    // m_pRS.reset(new RenderSystemGL);
    RenderSystem* rs = new RenderSystemGL(m_pContext);
    Error error = rs->Initialize();
    m_pContext->RegisterSubsystem(rs);

    if (!error) {
        _LoadDrivers();
        m_pMainWindow.reset(rs->CreateWindow());
    }

    LOGD2 << "[<] Main::Start()" << std::endl;

    return error;
}

Error Main::Run() {
    LOGD2 << "[>] Main::Run()" << std::endl;

    RenderSystem* rs = m_pContext->GetSubsystem<RenderSystem>();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    std::shared_ptr<Font> f(new Font(m_pContext, "./resources/fonts/Roboto-Regular.ttf"));
    UI ui(m_pContext);
    std::shared_ptr<Text> t(new Text(m_pContext));
    t->SetPosition(10.0f, 565.0f);
    t->SetFont(f);
    t->SetSize(24);

    ui.AddChild(t);

    // Build and compile our shader program
    Shader* ourShader = rs->CreateShader();
    ourShader->Attach("./codehero/shaders/textured.vert")
             .Attach("./codehero/shaders/textured.frag", {
                 {"NB_DIRECTIONAL_LIGHTS", "1"},
                 {"NB_POINT_LIGHTS", "4"},
             })
             .Link();

    Shader* textShader = rs->CreateShader();
    textShader->Attach("./codehero/shaders/text_basic.vert")
              .Attach("./codehero/shaders/text_basic.frag")
              .Link();
    textShader->Use();
    OrthoMatrix ortho(0, 600, 0, 600);
    rs->SetShaderParameter("projection", ortho);

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

    VertexBuffer* buffer = rs->CreateVertexBuffer();
    buffer->SetData(vertices, 36, VertexBuffer::MASK_Position | VertexBuffer::MASK_Normal | VertexBuffer::MASK_TexCoord);
    buffer->Unuse();

    // Load and create a texture
    Texture* texture1 = rs->CreateTexture();
    texture1->Load("./resources/images/container2.png");

    Texture* texture2 = rs->CreateTexture();
    texture2->Load("./resources/images/container2_specular.png");

    Model mdl(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/nanosuit/nanosuit.obj", mdl);

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
        rs->PollEvents();

        rs->ClearFrameBuffer();
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            fps = nbFrames;
            // printf("%f ms/frame\n", 1000.0/double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        t->SetText("FPS: " + std::to_string(fps));
        Vector3 color(0.5, 0.8f, 0.2f);
        textShader->Use();
        rs->SetShaderParameter("textColor", color);
        ui.Update();
        ui.Render();

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
        glUniform3f(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "pointLights[0].position"), pointLightPositions[0].x(), pointLightPositions[0].y(), pointLightPositions[0].z());
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

        rs->SetShaderParameter("view", camera.GetView());
        rs->SetShaderParameter("projection", projection);

        // Draw container
        buffer->Use();
        for (GLuint i = 0; i < 10; ++i) {
            Matrix4 model;
            model.Translate(cubePositions[i]);
            model.Rotate(glfwGetTime() * 20.0f * i, {1.0f, 0.3f, 0.5f});

            rs->SetShaderParameter("model", model);
            rs->SetViewport(viewportMiddleRight);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            rs->SetViewport(viewportBottomRight);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            rs->SetViewport(viewportTopRight);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            rs->SetViewport(viewportMain);
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

    LOGD2 << "[=] Main::_Initialize()" << std::endl;
}

void Main::_Cleanup() {
    m_pContext->GetSubsystem<RenderSystem>()->Cleanup();

    _UnloadDrivers();
}

void Main::_LoadDrivers() {
    LOGI << "Loading drivers..." << std::endl;
#ifdef DRIVER_PNG
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->AddCodec(new ImageCodecPNG(m_pContext));
#endif // DRIVER_PNG

#ifdef DRIVER_ASSIMP
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->AddCodec(new ModelCodecAssimp(m_pContext));
#endif // DRIVER_ASSIMP
    LOGI << "Drivers loaded..." << std::endl;
}

void Main::_UnloadDrivers() {
    LOGI << "Unloading drivers..." << std::endl;
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->ClearCodecs();
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->ClearCodecs();
    LOGI << "Drivers unloaded..." << std::endl;
}

} // namespace CodeHero
