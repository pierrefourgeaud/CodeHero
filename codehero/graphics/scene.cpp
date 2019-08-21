// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/scene.h"
#include <logger.h>
#include <queue>
#include "core/type_traits/objectdefinition.h"
#include "graphics/batch.h"
#include "graphics/camera.h"
#include "graphics/light.h"
#include "graphics/mesh.h"
#include "graphics/model.h"
#include "graphics/node.h"

namespace CodeHero {

Scene::Scene(const std::shared_ptr<EngineContext>& iContext) : Node(iContext) {
    m_IsScene = true;
}

Scene::~Scene() {}

void Scene::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Scene);
}

std::shared_ptr<Scene> Scene::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Scene>(iContext);
}

void Scene::RegisterSceneLight(const std::shared_ptr<Light>& iLight) {
    // TODO(pierre) We might need to check for multiple add of the same light
    //
    // By same light we mean, the same object but also at the same position with the same ID too...

    m_Lights.push_back(iLight);
}

void Scene::PrepareVertexLights() {
    // Reset all
    m_VertexLights.clear();
    m_VertexLights[Light::T_Directional] = std::vector<float>();
    m_VertexLights[Light::T_Point] = std::vector<float>();

    size_t nbLights = m_Lights.size();
    for (size_t i = 0; i < nbLights; ++i) {
        auto& l = m_Lights[i];
        switch (l->GetType()) {
            case Light::T_Directional: {
                auto& dir = l->GetDirection();
                m_VertexLights[Light::T_Directional].push_back(dir.x());
                m_VertexLights[Light::T_Directional].push_back(dir.y());
                m_VertexLights[Light::T_Directional].push_back(dir.z());
                m_VertexLights[Light::T_Directional].push_back(l->GetAmbientIntensity());
                m_VertexLights[Light::T_Directional].push_back(l->GetDiffuseIntensity());
                m_VertexLights[Light::T_Directional].push_back(l->GetSpecularIntensity());
                break;
            }
            case Light::T_Point: {
                auto& pos = l->GetNode()->GetPosition();
                m_VertexLights[Light::T_Point].push_back(pos.x());
                m_VertexLights[Light::T_Point].push_back(pos.y());
                m_VertexLights[Light::T_Point].push_back(pos.z());
                m_VertexLights[Light::T_Point].push_back(l->GetAmbientIntensity());
                m_VertexLights[Light::T_Point].push_back(l->GetDiffuseIntensity());
                m_VertexLights[Light::T_Point].push_back(l->GetSpecularIntensity());
                m_VertexLights[Light::T_Point].push_back(l->GetConstant());
                m_VertexLights[Light::T_Point].push_back(l->GetLinear());
                m_VertexLights[Light::T_Point].push_back(l->GetQuadratic());
                break;
            }
            // TODO(pierre) T_Spot
            default: break;
        }
    }
}

std::vector<Batch> Scene::GetBatches(const std::shared_ptr<Camera>& iCamera) {
    std::queue<Node*> m_NodesToProcess;
    m_NodesToProcess.push(this);

    std::vector<Batch> batches;

    auto cameraPos = iCamera->GetNode()->GetWorldTransform().Translation();
    while (!m_NodesToProcess.empty()) {
        Node* node = m_NodesToProcess.front();
        m_NodesToProcess.pop();

        // Add the children to the nodes to process
        auto children = node->GetChildren();
        size_t childrenSize = children.size();
        for (size_t i = 0; i < childrenSize; ++i) {
            m_NodesToProcess.push(children[i].get());
        }

        // then process the node
        auto drawables = node->GetComponents();
        size_t drawablesSize = drawables.size();
        for (size_t i = 0; i < drawablesSize; ++i) {
            auto drawable = drawables[i];
            switch (drawable->GetDrawableType()) {
                // case Drawable::DT_Light:
                //     lights.push_back(static_cast<Light*>(component));
                //     break;
                case Drawable::DT_Geometry: {
                    Model* model = static_cast<Model*>(drawable.get());
                    size_t nbMeshes = model->GetMeshes().size();
                    auto worldTransform = node->GetWorldTransform();
                    for (size_t m = 0; m < nbMeshes; ++m) {
                        Batch b;
                        b.SetMaterial(model->GetMeshes()[m]->GetMaterial());
                        b.SetMesh(model->GetMeshes()[m]);
                        b.SetWorldTransform(node->GetWorldTransform());
                        // TODO(pierre) This should probably be moved later. I guess
                        // the get batches should be done only once but the scene
                        // could be rendered multiple times from different cameras...
                        auto center = b.GetMesh()->GetCenter();
                        float distance = 0.0f;
                        // Skybox should have a distance to camera of 0.0f
                        if (model->GetTypeName() != "Skybox") {
                            distance = ((worldTransform * center) - cameraPos).Length();
                        }
                        b.SetDistanceFromCamera(distance);
                        b.SetVertexDirLights(&m_VertexLights[Light::T_Directional]);
                        b.SetVertexPointLights(&m_VertexLights[Light::T_Point]);
                        batches.push_back(std::move(b));
                    }
                    break;
                }
                default: break;
            }
        }
    }

    return batches;
}

} // namespace CodeHero
