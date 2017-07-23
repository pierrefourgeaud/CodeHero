// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_MODEL_H_
#define CODEHERO_GRAPHICS_MODEL_H_

#include <vector>
#include "core/object.h"

namespace CodeHero {

// Forward declaration
class Mesh;

class Model : public Object {
public:
    OBJECT(Model)
    explicit Model(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Model();

    void AddMesh(const std::shared_ptr<Mesh>& iMesh);

// private:
    std::vector<std::shared_ptr<Mesh>> m_Meshes;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_MODEL_H_
