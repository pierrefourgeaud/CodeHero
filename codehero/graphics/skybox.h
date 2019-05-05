// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SKYBOX_H_
#define CODEHERO_GRAPHICS_SKYBOX_H_

#include "graphics/model.h"

namespace CodeHero {

// Forward declaration
class Material;

class Skybox : public Model {
   public:
    OBJECT(Skybox, Model);

    Skybox(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Skybox();

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Skybox> Create(const std::shared_ptr<EngineContext>& iContext);

    void Initialize(const std::shared_ptr<Material>& iMaterial);
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SKYBOX_H_
