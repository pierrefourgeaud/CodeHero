// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "main/main.h"
#include <logger.h>
#include <filelogger.h>
#include <consolelogger.h>

#include "core/enginecontext.h"

#include "core/resourceloader.h"
#include "core/image.h"
#include "core/time.h"
#include "core/scopecleaner.h"
#include "core/serializable.h"

#include "graphics/renderwindow.h"
#include "graphics/viewport.h"
#include "graphics/camera.h"
#include "graphics/light.h"
#include "graphics/material.h"
#include "graphics/model.h"
#include "graphics/mesh.h"
#include "graphics/scene.h"
#include "graphics/cube.h"
#include "graphics/plane.h"
#include "graphics/batch.h"
#include "graphics/shader.h"
#include "graphics/shaderprogram.h"
#include "graphics/skybox.h"

#include "input/input.h"

#include "ui/button.h"
#include "ui/font.h"
#include "ui/label.h"
#include "ui/ui.h"
#include "ui/window.h"

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

#ifdef DRIVER_TGA
# include "drivers/tga/imagecodec_tga.h"
#endif // DRIVER_TGA

#ifdef DRIVER_ASSIMP
# include "drivers/assimp/modelcodec_assimp.h"
#endif // DRIVER_ASSIMP

#ifdef DRIVER_PUGIXML
# include "drivers/xml/serializablecodec_xml.h"
#endif // DRIVER_PUGIXML

const uint32_t g_Width = 1920;
const uint32_t g_Height = 1260;

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

    // Register objects first
    Scene::RegisterObject(m_pContext);
    Node::RegisterObject(m_pContext);
    Light::RegisterObject(m_pContext);
    Shader::RegisterObject(m_pContext);
    ShaderProgram::RegisterObject(m_pContext);
    Texture::RegisterObject(m_pContext);
    Material::RegisterObject(m_pContext);
    Skybox::RegisterObject(m_pContext);
    Model::RegisterObject(m_pContext);
    Mesh::RegisterObject(m_pContext);
    Plane::RegisterObject(m_pContext);
    Cube::RegisterObject(m_pContext);

    // Initialize the time as soon as possible
    Time* time = new Time(m_pContext);
    time->Initialize();
    m_pContext->RegisterSubsystem(time);

    ResourceLoader<Image>* rlImage = new ResourceLoader<Image>(m_pContext);
    rlImage->Initialize();
    m_pContext->RegisterSubsystem(rlImage);

    ResourceLoader<Model>* rlModel = new ResourceLoader<Model>(m_pContext);
    rlModel->Initialize();
    m_pContext->RegisterSubsystem(rlModel);

    ResourceLoader<Serializable>* rlSerializable = new ResourceLoader<Serializable>(m_pContext);
    rlSerializable->Initialize();
    m_pContext->RegisterSubsystem(rlSerializable);

    // m_pRS.reset(new RenderSystemGL);
    RenderSystem* rs = new RenderSystemGL(m_pContext);
    Error error = rs->Initialize();
    m_pContext->RegisterSubsystem(rs);

    if (!error) {
        _LoadDrivers();
        std::shared_ptr<RenderWindow> mainWindow = rs->CreateWindow(g_Width, g_Height);

        // This should be after window since some event might be tight to the window
        Input* input = new Input(m_pContext);
        input->Initialize();
        m_pContext->RegisterSubsystem(input);

        // Then we should add the input handle to the window
        mainWindow->SetInputHandler(m_pContext->GetSubsystem<Input>());
    }

    LOGD2 << "[<] Main::Start()" << std::endl;

    return error;
}

Error Main::Run() {
    LOGD2 << "[>] Main::Run()" << std::endl;

    // Cache the time to avoid repeating the query every loop
    Time* time = m_pContext->GetSubsystem<Time>();

    RenderSystem* rs = m_pContext->GetSubsystem<RenderSystem>();
    rs->SetBlendMode(true, BM_SrcAlpha, BM_OneMinusSrcAlpha);
    rs->SetCullMode(true);

    std::shared_ptr<RenderWindow> mainWindow = rs->GetWindow();
    UI ui(m_pContext);
    auto label = std::make_shared<Label>(m_pContext);
    label->SetPosition(15.0f, 15.0f);

    auto button = std::make_shared<Button>(m_pContext);
    button->SetPosition(15.0f, 55.0f);
    button->SetSize({ 150.0f, 50.0f });

    auto window = std::make_shared<Window>(m_pContext);
    window->SetPosition(20.0f, 185.0f);
    window->SetSize({ 300.0f, 400.0f });
    window->SetHeader("Info");

    ui.AddChild(window);
    window->AddChild(label);
    window->AddChild(button);

    auto textShaderVert = rs->CreateShader();
    textShaderVert->Load("./codehero/shaders/text_basic.vert").Compile();
    auto textShaderFrag = rs->CreateShader();
    textShaderFrag->Load("./codehero/shaders/text_basic.frag").Compile();
    auto textShader = rs->CreateShaderProgram();
    textShader->Attach(textShaderVert).Attach(textShaderFrag).Link();
    textShader->Use();
    Matrix4 ortho = Matrix4::MakeProjectionOrtho(0, g_Width, g_Height, 0);
    rs->SetShaderParameter("projection", ortho);

    auto lastTime = time->GetTimeMilliseconds();
    int nbFrames = 0;
    int fps = 0;

    std::shared_ptr<Scene> scene =
        m_pContext->GetSubsystem<ResourceLoader<Serializable>>()->Load<Scene>("./resources/samples/scene_test1.xml");

    auto shaderTexturedNoAlpha = m_pContext->GetSubsystem<ResourceLoader<Serializable>>()
            ->Load<ShaderProgram>("./resources/samples/shaderProgram_texturedNoAlpha.xml");
    auto shaderTexturedAlpha = m_pContext->GetSubsystem<ResourceLoader<Serializable>>()
            ->Load<ShaderProgram>("./resources/samples/shaderProgram_texturedAlpha.xml");

    std::shared_ptr<Node> nanoNode = scene->CreateChild();
    nanoNode->Translate({ 1.0f, -12.0f, 4.7f });
    auto nanoMdl = m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/nanosuit/nanosuit.obj");
    nanoNode->AddDrawable(nanoMdl);
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : nanoMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(shaderTexturedNoAlpha);
    }

    std::shared_ptr<Node> houseNode = scene->CreateChild();
    houseNode->Translate({ -15.0f, 0.0f, 5.0f });
    houseNode->SetRotation(Quaternion(0.0f, 180.0f, 0.0f));
    auto houseMdl =
        m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/small-house-diorama/Dio.obj");
    houseNode->AddDrawable(houseMdl);
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : houseMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(shaderTexturedAlpha);
    }

    std::shared_ptr<Node> rockNode = scene->CreateChild();
    rockNode->Translate({ -2.8f, -12.0f, 3.2f });
    auto rockMdl = m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/rock/rock.obj");
    rockNode->AddDrawable(rockMdl);
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : rockMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(shaderTexturedNoAlpha);
    }

    std::shared_ptr<Node> planetNode = scene->CreateChild();
    planetNode->Translate({ 12.8f, 12.0f, 23.2f });
    auto planetMdl = m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/planet/planet.obj");
    planetNode->AddDrawable(planetMdl);
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : planetMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(shaderTexturedNoAlpha);
    }

    std::shared_ptr<Node> treasureChestNode = scene->CreateChild();
    treasureChestNode->Translate({ -5.0f, -12.0f, 12.0f });
    treasureChestNode->Scale(0.015f);
    treasureChestNode->Rotate(Quaternion({ 0.0f, -45.0f, 0.0f }));
    auto treasureChestMdl =
        m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/treasure-chest/Chest.obj");
    treasureChestNode->AddDrawable(treasureChestMdl);
    std::shared_ptr<Texture> chestDiffuse(rs->CreateTexture());
    chestDiffuse->Load("./resources/models/treasure-chest/Chest_C.png");
    std::shared_ptr<Texture> chestSpecular(rs->CreateTexture());
    chestSpecular->Load("./resources/models/treasure-chest/Chest_M.png");
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : treasureChestMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(shaderTexturedNoAlpha);
        mesh->GetMaterial()->SetTexture(TextureUnit::TU_Diffuse, chestDiffuse);
        mesh->GetMaterial()->SetTexture(TextureUnit::TU_Specular, chestSpecular);
    }

    auto camera = std::make_shared<Camera>(m_pContext);
    camera->SetFov(45.0f);
    camera->SetAspectRatio((float)g_Width / (float)g_Height);
    camera->SetNearClip(0.1f);
    camera->SetFarClip(100.0f);
    std::shared_ptr<Node> cameraNode = scene->CreateChild();
    cameraNode->AddDrawable(camera);
    cameraNode->SetPosition({0.0f, 3.0f, -16.5f});
    float yaw = 0.0f;
    float pitch = 15.0f;
    cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));

    auto mainViewport = std::make_shared<Viewport>(0, 0, g_Width, g_Height);
    mainViewport->SetCamera(camera);
    mainViewport->SetScene(scene);
    rs->RegisterViewport(mainViewport);

    // Save the input to avoid doing a query at every frame
    Input* input = m_pContext->GetSubsystem<Input>();

    auto previous = time->GetTimeMilliseconds();

    while (!mainWindow->ShouldClose()) {
        input->Update();

        rs->ClearFrameBuffer();
        auto now = time->GetTimeMilliseconds();
        auto timeStep = (now - previous) / 1000.0f; // In seconds
        previous = now;
        nbFrames++;
        if (now - lastTime >= 1000) {
            fps = nbFrames;
            nbFrames = 0;
            lastTime = now;
        }

        // Check the inputs
        if (input->IsKeyPressed(Key::K_ESC)) {
            // On ESC we exit the example application
            mainWindow->SetShouldClose(true);
        }
        if (input->IsKeyPressed(Key::K_W)) {
            cameraNode->Translate(Vector3::Forward * 10.0f * timeStep);
        }
        if (input->IsKeyPressed(Key::K_S)) {
            cameraNode->Translate(Vector3::Backward * 10.0f * timeStep);
        }
        if (input->IsKeyPressed(Key::K_D)) {
            cameraNode->Translate(Vector3::Right * 10.0f * timeStep);
        }
        if (input->IsKeyPressed(Key::K_A)) {
            cameraNode->Translate(Vector3::Left * 10.0f * timeStep);
        }

        // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
        Vector2 mouseMove = input->GetMouseMove();
        yaw += 0.1f * mouseMove.x();
        pitch += 0.1f * mouseMove.y();
        pitch = Clamp(pitch, -90.0f, 90.0f);

        // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
        cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));

        label->SetText("FPS: " + std::to_string(fps));

        // TODO(pierre) This is for now, as we don't have a proper scene rendering
        // This should be removed ASAP
        cameraNode->Update();

        rs->Render();

        textShader->Use();
        ui.Update();
        ui.Render();

        mainWindow->SwapBuffers();

        input->EndFrame();
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

#ifdef DRIVER_TGA
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->AddCodec(new ImageCodecTGA(m_pContext));
#endif // DRIVER_TGA

#ifdef DRIVER_ASSIMP
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->AddCodec(new ModelCodecAssimp(m_pContext));
#endif // DRIVER_ASSIMP

#ifdef DRIVER_PUGIXML
    m_pContext->GetSubsystem<ResourceLoader<Serializable>>()->AddCodec(new SerializableCodecXML(m_pContext));
#endif // DRIVER_PUGIXML
    LOGI << "Drivers loaded..." << std::endl;
}

void Main::_UnloadDrivers() {
    LOGI << "Unloading drivers..." << std::endl;
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->ClearCodecs();
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->ClearCodecs();
    m_pContext->GetSubsystem<ResourceLoader<Serializable>>()->ClearCodecs();
    LOGI << "Drivers unloaded..." << std::endl;
}

} // namespace CodeHero
