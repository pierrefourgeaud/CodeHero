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
    Light::RegisterObject(m_pContext);
    Shader::RegisterObject(m_pContext);
    ShaderProgram::RegisterObject(m_pContext);

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
    std::shared_ptr<Font> f(new Font(m_pContext, "./resources/fonts/Roboto-Regular.ttf"));
    UI ui(m_pContext);
    std::shared_ptr<Text> t(new Text(m_pContext));
    t->SetPosition(20.0f, g_Height - 45.0f);
    t->SetFont(f);
    t->SetSize(38);

    ui.AddChild(t);

    auto textShaderVert = rs->CreateShader();
    textShaderVert->Load("./codehero/shaders/text_basic.vert").Compile();
    auto textShaderFrag = rs->CreateShader();
    textShaderFrag->Load("./codehero/shaders/text_basic.frag").Compile();
    auto textShader = rs->CreateShaderProgram();
    textShader->Attach(textShaderVert).Attach(textShaderFrag).Link();
    textShader->Use();
    Matrix4 ortho = Matrix4::MakeProjectionOrtho(0, g_Width, 0, g_Height);
    rs->SetShaderParameter("projection", ortho);

    // Load and create a texture
    auto crateDiffuse = rs->CreateTexture();
    crateDiffuse->Load("./resources/images/container2.png");

    auto crateSpecular = rs->CreateTexture();
    crateSpecular->Load("./resources/images/container2_specular.png");

    // Floor texture
    auto floorDiffuse = rs->CreateTexture();
    floorDiffuse->Load("./resources/images/floor_diffuse.PNG");
    auto floorSpecular = rs->CreateTexture();
    floorSpecular->Load("./resources/images/floor_specular.PNG");

    auto grassDiffuse = rs->CreateTexture();
    grassDiffuse->SetWrapMode(TC_U, TWM_ClampEdge);
    grassDiffuse->SetWrapMode(TC_V, TWM_ClampEdge);
    grassDiffuse->Load("./resources/images/grass.png");

    Vector3 cubePositions[] = {
        { 10.0f,  -10.5f, 10.0f},
        { 2.0f,  -10.5f, 15.0f},
        {-6.5f,  -10.5f, 5.5f},
        { 7.5f,  -10.5f, 0.0f},
        { 6.3f,  -10.5f, 5.5f}
    };

    Vector3 vegetationPositions[] = {
        {-2.5f, -10.0f, -0.48f},
        { 2.5f, -10.0f,  0.51f},
        { 0.0f, -10.0f,  0.7f},
        {-0.3f, -10.0f, -2.3f},
        { 1.0f, -10.0f, -0.6f}
    };

    Vector3 pointLightsPositions[] = {
        {-4.0f,  2.0f,  12.0f},
        { 0.0f,  3.0f,  3.0f}
    };

    auto lastTime = time->GetTimeMilliseconds();
    int nbFrames = 0;
    int fps = 0;

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    auto dirLightNode = scene->CreateChild();
    auto dirLight = dirLightNode->CreateDrawable<Light>(m_pContext, Light::T_Directional);
    m_pContext->GetSubsystem<ResourceLoader<Serializable>>()->Load("./resources/samples/dir_light1.xml", *dirLight.get());

    std::vector<Light> pointLights;
    for (size_t i = 0; i < 4; ++i) {
        auto pointLightNode = scene->CreateChild();
        auto pointLight = pointLightNode->CreateDrawable<Light>(m_pContext, Light::Type::T_Point)
            ->SetAmbientIntensity(0.05f)
            .SetDiffuseIntensity(0.5f)
            .SetSpecularIntensity(0.4f)
            .SetConstant(1.0f)
            .SetLinear(0.007f)
            .SetQuadratic(0.0002f);
        pointLightNode->SetPosition(pointLightsPositions[i]);
        pointLights.push_back(pointLight);
    }

    auto texturedShaderVert = rs->CreateShader();
    texturedShaderVert->Load("./codehero/shaders/textured.vert").Compile();
    auto texturedShaderNoAlphaFrag = rs->CreateShader();
    m_pContext->GetSubsystem<ResourceLoader<Serializable>>()->Load("./resources/samples/shader_texturedFragNoAlpha.xml", *texturedShaderNoAlphaFrag.get());
    auto crateShader = rs->CreateShaderProgram();
    crateShader->Attach(texturedShaderVert)
                .Attach(texturedShaderNoAlphaFrag)
                .Link();

    auto shaderTexturedAlpha = rs->CreateShaderProgram();
    m_pContext->GetSubsystem<ResourceLoader<Serializable>>()->Load("./resources/samples/shaderProgram_texturedAlpha.xml", *shaderTexturedAlpha.get());

    auto skyboxShaderVert = rs->CreateShader();
    skyboxShaderVert->Load("./codehero/shaders/skybox.vert").Compile();
    auto skyboxShaderFrag = rs->CreateShader();
    skyboxShaderFrag->Load("./codehero/shaders/skybox.frag").Compile();
    auto skyboxShader = rs->CreateShaderProgram();
    skyboxShader->Attach(skyboxShaderVert).Attach(skyboxShaderFrag).Link();

    auto skyboxTexture = rs->CreateTexture();
    skyboxTexture->SetType(Texture::T_Cube);
    // Should this be protected to be called always before setting picture
    skyboxTexture->SetWrapMode(TC_U, TWM_ClampEdge);
    skyboxTexture->SetWrapMode(TC_V, TWM_ClampEdge);
    skyboxTexture->SetWrapMode(TC_W, TWM_ClampEdge);
    skyboxTexture->Load({
        "./resources/images/skybox_clear_sky/right.jpg",
        "./resources/images/skybox_clear_sky/left.jpg",
        "./resources/images/skybox_clear_sky/top.jpg",
        "./resources/images/skybox_clear_sky/bottom.jpg",
        "./resources/images/skybox_clear_sky/back.jpg",
        "./resources/images/skybox_clear_sky/front.jpg"
    });

    auto skyboxMaterial = std::make_shared<Material>(m_pContext);
    skyboxMaterial->SetTexture(TU_Diffuse, std::shared_ptr<Texture>(skyboxTexture));
    skyboxMaterial->SetShaderProgram(skyboxShader);
    skyboxMaterial->SetDepthTest(false);

    auto skyboxNode = scene->CreateChild();
    auto skyboxMdl = skyboxNode->CreateDrawable<Skybox>(m_pContext);
    skyboxMdl->Initialize(skyboxMaterial);

    std::shared_ptr<Node> nanoNode = scene->CreateChild();
    nanoNode->Translate({ 1.0f, -12.0f, 4.7f });
    auto nanoMdl = nanoNode->CreateDrawable<Model>(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/nanosuit/nanosuit.obj", *nanoMdl.get());
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : nanoMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(crateShader);
        mesh->GetMaterial()->SetCullEnabled(true);
    }

    std::shared_ptr<Node> houseNode = scene->CreateChild();
    houseNode->Translate({ -15.0f, 0.0f, 5.0f });
    houseNode->SetRotation(Quaternion(0.0f, 180.0f, 0.0f));
    auto houseMdl = houseNode->CreateDrawable<Model>(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/small-house-diorama/Dio.obj", *houseMdl.get());
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : houseMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(shaderTexturedAlpha);
        mesh->GetMaterial()->SetCullEnabled(true);
    }

    std::shared_ptr<Node> rockNode = scene->CreateChild();
    rockNode->Translate({ -2.8f, -12.0f, 3.2f });
    auto rockMdl = rockNode->CreateDrawable<Model>(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/rock/rock.obj", *rockMdl.get());
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : rockMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(crateShader);
        mesh->GetMaterial()->SetCullEnabled(true);
    }

    std::shared_ptr<Node> planetNode = scene->CreateChild();
    planetNode->Translate({ 12.8f, 12.0f, 23.2f });
    auto planetMdl = planetNode->CreateDrawable<Model>(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/planet/planet.obj", *planetMdl.get());
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : planetMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(crateShader);
        mesh->GetMaterial()->SetCullEnabled(true);
    }

    std::shared_ptr<Node> treasureChestNode = scene->CreateChild();
    treasureChestNode->Translate({ -5.0f, -12.0f, 12.0f });
    treasureChestNode->Scale(0.015f);
    treasureChestNode->Rotate(Quaternion({ 0.0f, -45.0f, 0.0f }));
    auto treasureChestMdl = treasureChestNode->CreateDrawable<Model>(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/treasure-chest/Chest.obj", *treasureChestMdl.get());
    std::shared_ptr<Texture> chestDiffuse(rs->CreateTexture());
    chestDiffuse->Load("./resources/models/treasure-chest/Chest_C.png");
    std::shared_ptr<Texture> chestSpecular(rs->CreateTexture());
    chestSpecular->Load("./resources/models/treasure-chest/Chest_M.png");
    // TODO(pierre) This should be moved when we initialize the model hopefully
    for (auto& mesh : treasureChestMdl->GetMeshes()) {
        mesh->GetMaterial()->SetShaderProgram(crateShader);
        mesh->GetMaterial()->SetTexture(TextureUnit::TU_Diffuse, chestDiffuse);
        mesh->GetMaterial()->SetTexture(TextureUnit::TU_Specular, chestSpecular);
        mesh->GetMaterial()->SetCullEnabled(true);
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

    std::shared_ptr<Node> planeNode = scene->CreateChild();
    auto planeMdl = planeNode->CreateDrawable<Model>(m_pContext);
    auto floorMaterial = std::make_shared<Material>(m_pContext);
    floorMaterial->SetTexture(TU_Diffuse, std::shared_ptr<Texture>(floorDiffuse));
    floorMaterial->SetTexture(TU_Specular, std::shared_ptr<Texture>(floorSpecular));
    floorMaterial->SetShaderProgram(crateShader);
    floorMaterial->SetTextureCoordsOffset(5.0f, 5.0f);
    auto planePtr = std::make_shared<Plane>(m_pContext);
    planePtr->SetMaterial(floorMaterial);
    planeMdl->AddMesh(planePtr);
    planeNode->Scale({ 100.0f, 100.0f, 1.0f });
    planeNode->Translate({ 0, -12.1f, 0.0f });
    planeNode->Rotate(Quaternion(70.0f, 0.0f, 0.0f));

    auto cube = std::make_shared<Cube>(m_pContext);
    auto crateMaterial = std::make_shared<Material>(m_pContext);
    crateMaterial->SetTexture(TU_Diffuse, std::shared_ptr<Texture>(crateDiffuse));
    crateMaterial->SetTexture(TU_Specular, std::shared_ptr<Texture>(crateSpecular));
    crateMaterial->SetShaderProgram(crateShader);
    cube->SetMaterial(crateMaterial);
    for (auto& pos : cubePositions) {
        auto cubeNode = scene->CreateChild();
        cubeNode->Scale(3.0f);
        auto cubeMdl = cubeNode->CreateDrawable<Model>(m_pContext);
        cubeMdl->AddMesh(cube);
        cubeNode->SetPosition(pos);
    }

    auto grass = std::make_shared<Plane>(m_pContext);
    auto grassMaterial = std::make_shared<Material>(m_pContext);
    grassMaterial->SetTexture(TU_Diffuse, std::shared_ptr<Texture>(grassDiffuse));
    grassMaterial->SetShaderProgram(shaderTexturedAlpha);
    grass->SetMaterial(grassMaterial);
    for (auto& pos : vegetationPositions) {
        auto grassNode = scene->CreateChild();
        auto grassMdl = grassNode->CreateDrawable<Model>(m_pContext);
        grassMdl->AddMesh(grass);
        grassNode->SetPosition(pos);
        grassNode->Scale({ 5.0f, 5.0f, 0.0f });
    }

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

        t->SetText("FPS: " + std::to_string(fps));
        Vector3 color(0.5, 0.8f, 0.2f);
        textShader->Use();
        rs->SetShaderParameter("textColor", color);
        ui.Update();
        ui.Render();

        // TODO(pierre) This is for now, as we don't have a proper scene rendering
        // This should be removed ASAP
        cameraNode->Update();

        rs->Render();

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
