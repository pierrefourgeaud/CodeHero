// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "main/main.h"
#include <logger.h>
#include <filelogger.h>
#include <consolelogger.h>

#include "core/enginecontext.h"

#include "core/shader.h"
#include "core/resourceloader.h"
#include "core/image.h"
#include "core/time.h"

#include "graphics/renderwindow.h"
#include "graphics/viewport.h"
#include "graphics/camera.h"
#include "graphics/light.h"
#include "graphics/model.h"
#include "graphics/mesh.h"
#include "graphics/scene.h"
#include "graphics/cube.h"
#include "graphics/plane.h"

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

    Shader* textShader = rs->CreateShader();
    textShader->Attach("./codehero/shaders/text_basic.vert")
              .Attach("./codehero/shaders/text_basic.frag")
              .Link();
    textShader->Use();
    Matrix4 ortho = Matrix4::MakeProjectionOrtho(0, g_Width, 0, g_Height);
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

    Texture* grassTexture = rs->CreateTexture();
    grassTexture->Load("./resources/images/grass.png");

    Model mdl2(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/small-house-diorama/Dio.obj", mdl2);

    Cube cube(m_pContext);
    Plane grass(m_pContext);

    Vector3 cubePositions[] = {
        { 0.0f,  0.0f, 0.0f},
        { 2.0f,  5.0f, 15.0f},
        {-1.5f, -2.2f, 2.5f},
        {-3.8f, -2.0f, 12.3f},
        { 2.4f, -0.4f, 3.5f},
        {-1.7f,  3.0f, 7.5f},
        { 1.3f, -2.0f, 2.5f},
        { 1.5f,  2.0f, 2.5f},
        { 1.5f,  0.2f, 1.5f},
        {-1.3f,  1.0f, 1.5f}
    };

    Vector3 vegetationPositions[] = {
        {-2.5f, -10.0f, -0.48f},
        { 2.5f, -10.0f,  0.51f},
        { 0.0f, -10.0f,  0.7f},
        {-0.3f, -10.0f, -2.3f},
        { 1.0f, -10.0f, -0.6f}
    };

    Vector3 pointLightsPositions[] = {
        { 0.7f,  0.2f,  2.0f},
        { 2.3f, -3.3f, -4.0f},
        {-4.0f,  2.0f,  12.0f},
        { 0.0f,  3.0f,  3.0f}
    };

    auto lastTime = time->GetTimeMilliseconds();
    int nbFrames = 0;
    int fps = 0;

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    auto dirLightNode = scene->CreateChild();
    auto dirLight = dirLightNode->CreateDrawable<Light>(m_pContext, Light::Type::T_Directional)
        ->SetDirection({-0.2f, -1.0f, 0.3f})
        .SetAmbientIntensity(0.45f)
        .SetDiffuseIntensity(0.8f)
        .SetSpecularIntensity(0.5f);

    std::vector<Light> pointLights;
    for (size_t i = 0; i < 4; ++i) {
        auto pointLightNode = scene->CreateChild();
        auto pointLight = pointLightNode->CreateDrawable<Light>(m_pContext, Light::Type::T_Point)
            ->SetAmbientIntensity(0.05f)
            .SetDiffuseIntensity(0.8f)
            .SetSpecularIntensity(1.0f)
            .SetConstant(1.0f)
            .SetLinear(0.007f)
            .SetQuadratic(0.0002f);
        pointLightNode->SetPosition(pointLightsPositions[i]);
        pointLights.push_back(pointLight);
    }

    Shader* crateShader = rs->CreateShader();
    crateShader->Attach("./codehero/shaders/textured.vert")
                .Attach("./codehero/shaders/textured.frag", {
                    {"NB_DIRECTIONAL_LIGHTS", "1"},
                    {"NB_POINT_LIGHTS", std::to_string(pointLights.size())},
                })
                .Link();

    Shader* grassShader = rs->CreateShader();
    grassShader->Attach("./codehero/shaders/textured.vert")
                .Attach("./codehero/shaders/textured.frag", {
                    { "NB_DIRECTIONAL_LIGHTS", "1" },
                    { "NB_POINT_LIGHTS", std::to_string(pointLights.size()) },
                    { "ALPHAMASK", ""}
                })
                .Link();

    std::shared_ptr<Node> node = scene->CreateChild();
    auto nanoMdl = node->CreateDrawable<Model>(m_pContext);
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->Load("./resources/models/nanosuit/nanosuit.obj", *nanoMdl.get());

    auto camera = std::make_shared<Camera>(m_pContext);
    std::shared_ptr<Node> cameraNode = scene->CreateChild();
    cameraNode->AddDrawable(camera);
    cameraNode->SetPosition({0.0f, 3.0f, -16.5f});
    float yaw = 0.0f;
    float pitch = 15.0f;
    cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));

    std::shared_ptr<Node> planeNode = scene->CreateChild();
    auto planeMdl = planeNode->CreateDrawable<Model>(m_pContext);
    auto planePtr = std::make_shared<Plane>(m_pContext);
    planePtr->SetTextures({
        { TU_Diffuse, std::shared_ptr<Texture>(floorDiffuse) },
        { TU_Specular, std::shared_ptr<Texture>(floorSpecular) }
    });
    planeMdl->AddMesh(planePtr);
    planeNode->Scale({ 100.0f, 100.0f, 1.0f });
    planeNode->Translate({ 0, -12.1f, 0.0f });
    planeNode->Rotate(Quaternion(70.0f, 0.0f, 0.0f));

    std::vector<std::shared_ptr<Viewport>> viewports;
    viewports.push_back(std::make_shared<Viewport>(0, 0, g_Width, g_Height));
    viewports.push_back(std::make_shared<Viewport>(g_Width * 0.7f, g_Height * 0.6f, g_Width / 4, g_Height / 4));

    auto cubeVertices = cube.GetVertices();
    auto grassVertices = grass.GetVertices();

    // Save the input to avoid doing a query at every frame
    Input* input = m_pContext->GetSubsystem<Input>();

    Matrix4 projection = Matrix4::MakeProjectionPerspective(45.0f, (float)g_Width / (float)g_Height, 0.1f, 100.0f);
    auto previous = time->GetTimeMilliseconds();

    Matrix4 modelNano;
    modelNano.Translate({1.0f, -12.0f, 4.7f});

    Matrix4 modelHouse;
    modelHouse.Translate({ -15.0f, 0.0f, 5.0f });
    modelHouse.Rotate(180.0f, { 0.0f, 1.0f, 0.0f });

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
        if (input->IsKeyPressed(Key::K_Q)) {
            yaw -= 10.0f * timeStep;
            cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
        }
        if (input->IsKeyPressed(Key::K_E)) {
            yaw += 10.0f * timeStep;
            cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
        }
        if (input->IsKeyPressed(Key::K_R)) {
            pitch -= 10.0f * timeStep;
            pitch = Clamp(pitch, -90.0f, 90.0f);
            cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
        }
        if (input->IsKeyPressed(Key::K_F)) {
            pitch += 10.0f * timeStep;
            pitch = Clamp(pitch, -90.0f, 90.0f);
            cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
        }

        // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
        IntVector2 mouseMove = input->GetMouseMove();
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

        // Draw the triangle
        crateShader->Use();

        rs->SetShaderParameter("dirLight[0].direction", dirLight.GetDirection());
        rs->SetShaderParameter("dirLight[0].base.ambientIntensity", dirLight.GetAmbientIntensity());
        rs->SetShaderParameter("dirLight[0].base.diffuseIntensity", dirLight.GetDiffuseIntensity());
        rs->SetShaderParameter("dirLight[0].base.specularIntensity", dirLight.GetSpecularIntensity());

        // TODO(pierre) This should be optimized somehow
        //              The FPS is droping - One of the main reason is the string concatenation (urgghhh ugly)
        //              I am leaving as is for now, I am still building the proper rendering pipeline, this will change
        size_t pLights = pointLights.size();
        for (size_t i = 0; i < pLights; ++i) {
            std::string base = "pointLights[" + std::to_string(i) + "].";
            rs->SetShaderParameter(base + "position", pointLights[i].GetNode()->GetPosition());
            rs->SetShaderParameter(base + "base.ambientIntensity", pointLights[i].GetAmbientIntensity());
            rs->SetShaderParameter(base + "base.diffuseIntensity", pointLights[i].GetDiffuseIntensity());
            rs->SetShaderParameter(base + "base.specularIntensity", pointLights[i].GetSpecularIntensity());
            float atten[3] = {pointLights[i].GetConstant(), pointLights[i].GetLinear(), pointLights[i].GetQuadratic()};
            rs->SetShaderParameter(base + "attenuation[0]", atten, sizeof(atten));
        }

        rs->SetShaderParameter("view", camera->GetView());
        rs->SetShaderParameter("projection", projection);

        // TODO(pierre) This is for now, as we don't have a proper scene rendering
        // This should be removed ASAP
        cameraNode->Update();

        // TODO(pierre) This code is plain ugly. The idea is to demonstrate the loading and displaying of a model.
        // We should split that code properly with scene node, model, mesh, materials.
        // Please do not take that for production code.
        rs->SetShaderParameter("model", modelNano);
        size_t s = nanoMdl->m_Meshes.size();
        for (int i = 0; i < s; ++i) {
            auto diff = nanoMdl->m_Meshes[i]->GetTexture(TU_Diffuse);
            if (diff) {
                diff->Bind(0);
                rs->SetShaderParameter("material.diffuse", 0);
            }
            auto spec = nanoMdl->m_Meshes[i]->GetTexture(TU_Diffuse);
            if (spec) {
                spec->Bind(1);
                rs->SetShaderParameter("material.specular", 1);
            }
            rs->SetShaderParameter("material.shininess", 32.0f);

            nanoMdl->m_Meshes[i]->GetVertices()->Use();

            rs->Draw(PT_Triangles, nanoMdl->m_Meshes[i]->GetIndices()->GetSize());
        }

        // Bind Textures using texture units
        texture1->Bind(0);
        rs->SetShaderParameter("material.diffuse", 0);
        texture2->Bind(1);
        rs->SetShaderParameter("material.specular", 1);

        rs->SetShaderParameter("material.shininess", 32.0f);

        float duration = now / 1000.0f;

        // Draw container
        cubeVertices->Use();
        for (uint32_t i = 0; i < 10; ++i) {
            Matrix4 model;
            model.Translate(cubePositions[i]);
            model.Rotate(duration * 20.0f * i, {1.0f, 0.3f, 0.5f});

            rs->SetShaderParameter("model", model);
            for (size_t i = viewports.size(); i > 0; --i) {
                rs->SetViewport(viewports[i - 1].get());
                rs->Draw(PT_Triangles, 0, cubeVertices->GetVertexCount());
            }
        }
        cubeVertices->Unuse();

        rs->SetCullMode(false);

        rs->SetShaderParameter("model", planeNode->GetWorldTransform());
        size_t sss = planeMdl->m_Meshes.size();
        for (int i = 0; i < sss; ++i) {
            auto diff = planeMdl->m_Meshes[i]->GetTexture(TU_Diffuse);
            if (diff) {
                diff->Bind(0);
                rs->SetShaderParameter("material.diffuse", 0);
            }
            auto spec = planeMdl->m_Meshes[i]->GetTexture(TU_Diffuse);
            if (spec) {
                spec->Bind(1);
                rs->SetShaderParameter("material.specular", 1);
            }
            rs->SetShaderParameter("material.shininess", 32.0f);

            planeMdl->m_Meshes[i]->GetVertices()->Use();

            if (planeMdl->m_Meshes[i]->GetIndices().get() && planeMdl->m_Meshes[i]->GetIndices()->GetSize() > 0) {
                rs->Draw(PT_Triangles, planeMdl->m_Meshes[i]->GetIndices()->GetSize());
            } else {
                rs->Draw(PT_Triangles, 0, planeMdl->m_Meshes[i]->GetVertices()->GetVertexCount());
            }
        }

        grassShader->Use();

        rs->SetShaderParameter("dirLight[0].direction", dirLight.GetDirection());
        rs->SetShaderParameter("dirLight[0].base.ambientIntensity", dirLight.GetAmbientIntensity());
        rs->SetShaderParameter("dirLight[0].base.diffuseIntensity", dirLight.GetDiffuseIntensity());
        rs->SetShaderParameter("dirLight[0].base.specularIntensity", dirLight.GetSpecularIntensity());

        // TODO(pierre) This should be optimized somehow
        //              The FPS is droping - One of the main reason is the string concatenation (urgghhh ugly)
        //              I am leaving as is for now, I am still building the proper rendering pipeline, this will change
        for (size_t i = 0; i < pLights; ++i) {
            std::string base = "pointLights[" + std::to_string(i) + "].";
            rs->SetShaderParameter(base + "position", pointLights[i].GetNode()->GetPosition());
            rs->SetShaderParameter(base + "base.ambientIntensity", pointLights[i].GetAmbientIntensity());
            rs->SetShaderParameter(base + "base.diffuseIntensity", pointLights[i].GetDiffuseIntensity());
            rs->SetShaderParameter(base + "base.specularIntensity", pointLights[i].GetSpecularIntensity());
            float atten[3] = { pointLights[i].GetConstant(), pointLights[i].GetLinear(), pointLights[i].GetQuadratic() };
            rs->SetShaderParameter(base + "attenuation[0]", atten, sizeof(atten));
        }

        rs->SetShaderParameter("view", camera->GetView());
        rs->SetShaderParameter("projection", projection);

        grassTexture->Bind(0);
        rs->SetShaderParameter("material.diffuse", 0);
        rs->SetShaderParameter("material.shininess", 32.0f);
        grassVertices->Use();
        for (size_t i = 0; i < 5; ++i) {
            Matrix4 model;
            model.Scale({ 5.0f, 5.0f, 0.0f });
            model.Translate(vegetationPositions[i]);

            rs->SetShaderParameter("model", model);
            for (size_t i = viewports.size(); i > 0; --i) {
                rs->SetViewport(viewports[i - 1].get());
                rs->Draw(PT_Triangles, 0, 6);
            }
        }
        grassVertices->Unuse();

        rs->SetCullMode(true);
        // TODO(pierre) This code is plain ugly. The idea is to demonstrate the loading and displaying of a model.
        // We should split that code properly with scene node, model, mesh, materials.
        // Please do not take that for production code.
        rs->SetShaderParameter("model", modelHouse);
        size_t s2 = mdl2.m_Meshes.size();
        for (int i = 0; i < s2; ++i) {
            auto diff = mdl2.m_Meshes[i]->GetTexture(TU_Diffuse);
            if (diff) {
                diff->Bind(0);
                rs->SetShaderParameter("material.diffuse", 0);
            }
            auto spec = mdl2.m_Meshes[i]->GetTexture(TU_Diffuse);
            if (spec) {
                spec->Bind(1);
                rs->SetShaderParameter("material.specular", 1);
            }
            rs->SetShaderParameter("material.shininess", 32.0f);

            mdl2.m_Meshes[i]->GetVertices()->Use();

            rs->Draw(PT_Triangles, mdl2.m_Meshes[i]->GetIndices()->GetSize());
        }

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
    LOGI << "Drivers loaded..." << std::endl;
}

void Main::_UnloadDrivers() {
    LOGI << "Unloading drivers..." << std::endl;
    m_pContext->GetSubsystem<ResourceLoader<Image>>()->ClearCodecs();
    m_pContext->GetSubsystem<ResourceLoader<Model>>()->ClearCodecs();
    LOGI << "Drivers unloaded..." << std::endl;
}

} // namespace CodeHero
