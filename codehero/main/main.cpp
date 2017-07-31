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
#include "graphics/light.h"
#include "graphics/model.h"
#include "graphics/mesh.h"
#include "graphics/scene.h"
#include "graphics/cube.h"
#include "graphics/plane.h"

#include "ui/font.h"
#include "ui/ui.h"
#include "ui/text.h"

#include "rendersystems/GL/rendersystemGL.h"
#include "rendersystems/GL/textureGL.h"

#include "core/math/vector3.h"
#include "core/math/matrix4.h"

#include "graphics/indexbuffer.h"
#include "graphics/vertexbuffer.h"

#ifdef DRIVER_PNG
# include "drivers/png/imagecodec_png.h"
#endif // DRIVER_PNG

#ifdef DRIVER_JPG
# include "drivers/jpg/imagecodec_jpg.h"
#endif // DRIVER_JPG

#ifdef DRIVER_DDS
# include "drivers/dds/imagecodec_dds.h"
#endif // DRIVER_DDS

#ifdef DRIVER_ASSIMP
# include "drivers/assimp/modelcodec_assimp.h"
#endif // DRIVER_ASSIMP

const uint32_t g_Width = 1920;
const uint32_t g_Height = 1440;

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
        m_pMainWindow.reset(rs->CreateWindow(g_Width, g_Height));
    }

    LOGD2 << "[<] Main::Start()" << std::endl;

    return error;
}

Error Main::Run() {
    LOGD2 << "[>] Main::Run()" << std::endl;

    RenderSystem* rs = m_pContext->GetSubsystem<RenderSystem>();
    std::shared_ptr<Font> f(new Font(m_pContext, "./resources/fonts/Roboto-Regular.ttf"));
    UI ui(m_pContext);
    std::shared_ptr<Text> t(new Text(m_pContext));
    t->SetPosition(10.0f, g_Height * 0.95);
    t->SetFont(f);
    t->SetSize(38);

    ui.AddChild(t);

    // Create scene lights
    std::vector<Light> dirLights;
    dirLights.push_back(Light(m_pContext, Light::Type::T_Directional).SetDirection({-0.2f, -1.0f, -0.3f})
                                                                     .SetAmbientIntensity(0.45f)
                                                                     .SetDiffuseIntensity(0.8f)
                                                                     .SetSpecularIntensity(0.5f));

    std::vector<Light> pointLights;
    pointLights.push_back(Light(m_pContext, Light::Type::T_Point).SetPosition({0.7f, 0.2f, 2.0f})
                                                                 .SetAmbientIntensity(0.05f)
                                                                 .SetDiffuseIntensity(0.8f)
                                                                 .SetSpecularIntensity(1.0f)
                                                                 .SetConstant(1.0f)
                                                                 .SetLinear(0.007f)
                                                                 .SetQuadratic(0.0002f));
    pointLights.push_back(Light(m_pContext, Light::Type::T_Point).SetPosition({2.3f, -3.3f, -4.0f})
                                                                 .SetAmbientIntensity(0.05f)
                                                                 .SetDiffuseIntensity(0.8f)
                                                                 .SetSpecularIntensity(1.0f)
                                                                 .SetConstant(1.0f)
                                                                 .SetLinear(0.007f)
                                                                 .SetQuadratic(0.0002f));
    pointLights.push_back(Light(m_pContext, Light::Type::T_Point).SetPosition({-4.0f, 2.0f, -12.0f})
                                                                 .SetAmbientIntensity(0.05f)
                                                                 .SetDiffuseIntensity(0.8f)
                                                                 .SetSpecularIntensity(1.0f)
                                                                 .SetConstant(1.0f)
                                                                 .SetLinear(0.007f)
                                                                 .SetQuadratic(0.0002f));
    pointLights.push_back(Light(m_pContext, Light::Type::T_Point).SetPosition({0.0f, 0.0f, -3.0f})
                                                                 .SetAmbientIntensity(0.05f)
                                                                 .SetDiffuseIntensity(0.8f)
                                                                 .SetSpecularIntensity(1.0f)
                                                                 .SetConstant(1.0f)
                                                                 .SetLinear(0.007f)
                                                                 .SetQuadratic(0.0002f));

    // Build and compile our shader program
    Shader* crateShader = rs->CreateShader();
    crateShader->Attach("./codehero/shaders/textured.vert")
             .Attach("./codehero/shaders/textured.frag", {
                 {"NB_DIRECTIONAL_LIGHTS", std::to_string(dirLights.size())},
                 {"NB_POINT_LIGHTS", std::to_string(pointLights.size())},
             })
             .Link();

    Shader* textShader = rs->CreateShader();
    textShader->Attach("./codehero/shaders/text_basic.vert")
              .Attach("./codehero/shaders/text_basic.frag")
              .Link();
    textShader->Use();
    OrthoMatrix ortho(0, g_Width * 0.75, 0, g_Width * 0.75);
    rs->SetShaderParameter("projection", ortho);

    // Load and create a texture
    Texture* texture1 = rs->CreateTexture();
    texture1->Load("./resources/images/container2.png");

    Texture* texture2 = rs->CreateTexture();
    texture2->Load("./resources/images/container2_specular.png");

    // Floor texture
    Texture* floorDiffuse = rs->CreateTexture();
    floorDiffuse->Load("./resources/images/floor_diffuse.PNG");
    Texture* floorSpecular = rs->CreateTexture();
    floorSpecular->Load("./resources/images/floor_specular.PNG");

    Model mdl(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/nanosuit/nanosuit.obj", mdl);

    Cube cube(m_pContext);
    Plane plane(m_pContext);

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

    Scene scene;
    Node* node = scene.CreateChild();
    node->AddDrawable(&mdl);
    std::vector<std::shared_ptr<Viewport>> viewports;
    viewports.push_back(std::make_shared<Viewport>(0, 0, g_Width * 0.75, g_Height));
    for (size_t i = 0; i < 3; ++i) {
        viewports.push_back(std::make_shared<Viewport>(g_Width * 0.75, (i * g_Height / 3), g_Width / 4, g_Height / 3));
    }

    Camera camera({0.0f, 3.2f, 6.5f}, {0.0f, 1.0f, 0.0f});

    Matrix4 modelFloor;
    modelFloor.Scale({ 100.0f, 1.0f, 100.0f });
    modelFloor.Translate({ 0, -40.0f, 0 });
    modelFloor.Rotate(45.0f, { 1.0f, 0.0f, 0.0f });

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
        crateShader->Use();

        rs->SetShaderParameter("dirLight[0].direction", dirLights[0].GetDirection());
        rs->SetShaderParameter("dirLight[0].base.ambientIntensity", dirLights[0].GetAmbientIntensity());
        rs->SetShaderParameter("dirLight[0].base.diffuseIntensity", dirLights[0].GetDiffuseIntensity());
        rs->SetShaderParameter("dirLight[0].base.specularIntensity", dirLights[0].GetSpecularIntensity());

        // TODO(pierre) This should be optimized somehow
        //              The FPS is droping - One of the main reason is the string concatenation (urgghhh ugly)
        //              I am leaving as is for now, I am still building the proper rendering pipeline, this will change
        size_t pLights = pointLights.size();
        for (size_t i = 0; i < pLights; ++i) {
            std::string base = "pointLights[" + std::to_string(i) + "].";
            rs->SetShaderParameter(base + "position", pointLights[i].GetPosition());
            rs->SetShaderParameter(base + "base.ambientIntensity", pointLights[i].GetAmbientIntensity());
            rs->SetShaderParameter(base + "base.diffuseIntensity", pointLights[i].GetDiffuseIntensity());
            rs->SetShaderParameter(base + "base.specularIntensity", pointLights[i].GetSpecularIntensity());
            rs->SetShaderParameter(base + "constant", pointLights[i].GetConstant());
            rs->SetShaderParameter(base + "linear", pointLights[i].GetLinear());
            rs->SetShaderParameter(base + "quadratic", pointLights[i].GetQuadratic());
        }

        PerspectiveMatrix projection(45.0f, g_Width / g_Height, 0.1f, 100.0f);

        rs->SetShaderParameter("view", camera.GetView());
        rs->SetShaderParameter("projection", projection);

        // TODO(pierre) This code is plain ugly. The idea is to demonstrate the loading and displaying of a model.
        // We should split that code properly with scene node, model, mesh, materials.
        // Please do not take that for production code.
        Matrix4 mod;
        mod.Translate({ 1.0f,  -12.0f, -10.0f});
        rs->SetShaderParameter("model", mod);
        size_t s = mdl.m_Meshes.size();
        for (int i = 0; i < s; ++i) {
            size_t tSize = mdl.m_Meshes[i]->GetTextures().at("texture_diffuse").size();
            uint32_t j = 0;
            for (j = 0; j < tSize; ++j) {
                mdl.m_Meshes[i]->GetTextures().at("texture_diffuse")[j]->Bind(j);
                glUniform1i(glGetUniformLocation(crateShader->GetGPUObject().intHandle, "material.diffuse"), j);
            }
            tSize = mdl.m_Meshes[i]->GetTextures().at("texture_specular").size();
            for (uint32_t k = 0; k < tSize; ++k) {
                mdl.m_Meshes[i]->GetTextures().at("texture_specular")[k]->Bind(j + k);
                glUniform1i(glGetUniformLocation(crateShader->GetGPUObject().intHandle, "material.specular"), j + k);
            }

            mdl.m_Meshes[i]->GetVertices()->Use();

            glDrawElements(GL_TRIANGLES, mdl.m_Meshes[i]->GetIndices()->GetSize(), GL_UNSIGNED_INT, 0);
        }

        // Bind Textures using texture units
        texture1->Bind(0);
        glUniform1i(glGetUniformLocation(crateShader->GetGPUObject().intHandle, "material.diffuse"), 0);
        texture2->Bind(1);
        glUniform1i(glGetUniformLocation(crateShader->GetGPUObject().intHandle, "material.specular"), 1);

        glUniform1f(glGetUniformLocation(crateShader->GetGPUObject().intHandle, "material.shininess"), 32.0f);

        // Draw container
        cube.GetVertices()->Use();
        for (GLuint i = 0; i < 10; ++i) {
            Matrix4 model;
            model.Translate(cubePositions[i]);
            model.Rotate(glfwGetTime() * 20.0f * i, {1.0f, 0.3f, 0.5f});

            rs->SetShaderParameter("model", model);
            for (size_t i = viewports.size(); i > 0; --i) {
                rs->SetViewport(viewports[i - 1].get());
                rs->Draw(PT_Triangles, 0, 36);
            }
        }
        cube.GetVertices()->Unuse();

        // Bind Textures using texture units
        floorDiffuse->Bind(0);
        glUniform1i(glGetUniformLocation(crateShader->GetGPUObject().intHandle, "material.diffuse"), 0);
        floorSpecular->Bind(1);
        glUniform1i(glGetUniformLocation(crateShader->GetGPUObject().intHandle, "material.specular"), 1);

        glUniform1f(glGetUniformLocation(crateShader->GetGPUObject().intHandle, "material.shininess"), 32.0f);

        plane.GetVertices()->Use();
        rs->SetShaderParameter("model", modelFloor);
        for (size_t i = viewports.size(); i > 0; --i) {
            rs->SetViewport(viewports[i - 1].get());
            rs->Draw(PT_Triangles, 0, 6);
        }
        plane.GetVertices()->Use();

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

#ifdef DRIVER_JPG
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->AddCodec(new ImageCodecJPG(m_pContext));
#endif // DRIVER_JPG

#ifdef DRIVER_DDS
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->AddCodec(new ImageCodecDDS(m_pContext));
#endif // DRIVER_DDS

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
