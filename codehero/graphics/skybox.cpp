// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/skybox.h"
#include "graphics/cube.h"

namespace CodeHero {

Skybox::Skybox(const std::shared_ptr<EngineContext>& iContext)
    : Model(iContext) {}

Skybox::~Skybox() {}

void Skybox::Initialize(const std::shared_ptr<Material>& iMaterial) {
    auto mesh = std::make_shared<Cube>(m_pContext);
    mesh->SetMaterial(iMaterial);
    m_Meshes.push_back(mesh);
}

} // namespace CodeHero