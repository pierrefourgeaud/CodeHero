// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_MODEL_H_
#define CODEHERO_GRAPHICS_MODEL_H_

#include <vector>
#include "core/object.h"
#include "graphics/drawable.h"

namespace CodeHero {

// Forward declaration
class Mesh;

class Model : public Drawable {
public:
    OBJECT(Model, Drawable)

    explicit Model(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Model();

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Model> Create(const std::shared_ptr<EngineContext>& iContext);

    void AddMesh(const std::shared_ptr<Mesh>& iMesh);
    const std::vector<std::shared_ptr<Mesh>>& GetMeshes() const { return m_Meshes; }

protected:
    std::vector<std::shared_ptr<Mesh>> m_Meshes;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_MODEL_H_
