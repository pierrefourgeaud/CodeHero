// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SCENE_H_
#define CODEHERO_GRAPHICS_SCENE_H_ 

#include <memory>
#include <unordered_map>
#include <vector>
#include "graphics/light.h"
#include "graphics/node.h"
#include "core/unordered_map.h"

namespace CodeHero {

// Forward declaration
class Batch;
class Camera;

// Scene is simply a rootNode.
// It will inerit everything everything for the node
// But with extra properties
class Scene : public Node {
public:
    OBJECT(Scene, Node);

    Scene(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Scene();

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Scene> Create(const std::shared_ptr<EngineContext>& iContext);

    // Facility for rendering
    void RegisterSceneLight(const std::shared_ptr<Light>& iLight);

    void PrepareVertexLights();

    // TODO(pierre) There is optimization that should be done here
    //    - We can use a good data structure to help localization of object, and by default not process the too far/
    //      not visible ones
    //    - We should use a worker queue to retrieve the batches
    std::vector<Batch> GetBatches();

    const UnorderedMap<Light::Type, std::vector<float>>& GetVertexLights() const { return m_VertexLights; }

private:
    std::vector<std::shared_ptr<Light>> m_Lights;

    // Cached vertex lights
    UnorderedMap<Light::Type, std::vector<float>> m_VertexLights;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SCENE_H_
