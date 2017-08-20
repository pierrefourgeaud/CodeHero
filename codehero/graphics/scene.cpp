// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/scene.h"
#include <logger.h>
#include "graphics/light.h"
#include "graphics/node.h"
#include <queue>

namespace CodeHero {

Scene::Scene() {}

Scene::~Scene() {}

void Scene::RegisterSceneLight(const std::shared_ptr<Light>& iLight) {
    // Check if the light in question is not registered already
    auto light = std::find(m_Lights.begin(), m_Lights.end(), iLight);
    if (light != std::end(m_Lights)) {
        // Light exist, log a warning and return
        LOGW << "Scene: Registration of light failed. Object already registered." << std::endl;
        return;
    }

    m_Lights.push_back(iLight);
}

void Scene::Render(Camera* iCamera) {
    (void)iCamera;
    /*
    std::queue<Node*> m_NodesToProcess;
    m_NodesToProcess.push(m_pRootNode);
    std::vector<Light*> lights;
    std::vector<Mesh*> meshes;
    while (!m_NodesToProcess.empty()) {
        Node* node = m_NodesToProcess.front();
        m_NodesToProcess.pop();
        
        // Add the children to the nodes to process
        auto children = node->GetChildren();
        size_t childrenSize = children.size();
        for (size_t i = 0; i < childrenSize; ++i) {
            m_NodesToProcess.push(children[i]);
        }

        // then process the node
        auto components = node->GetComponents();
        size_t componentsSize = components.size();
        for (int i = 0; i < componentsSize; ++i) {
            Component* component = components[i];
            switch (component->GetDrawableType()) {
                case Component::DT_Light:
                    lights.push_back(static_cast<Light*>(component));
                    break;
                case Component::DT_Geometry:
                default:
                    meshes.push_back(static_cast<Mesh*>(component));
                    break;
            }
        }
    }

    size_t lightsSize = lights.size();
    for (int i = 0; i < lightsSize; ++i) {
        lights[i]->Draw(iCamera);
    }

    size_t meshesSize = meshes.size();
    for (int i = 0; i < meshesSize; ++i) {
        meshes[i]->Draw(iCamera);
    }*/
}

} // namespace CodeHero

