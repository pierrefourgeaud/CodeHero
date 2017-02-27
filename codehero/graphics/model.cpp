// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/model.h"

namespace CodeHero {

Model::Model(const std::shared_ptr<EngineContext>& iContext)
    : Object(iContext) {}

Model::~Model() {}

void Model::AddMesh(const std::shared_ptr<Mesh>& iMesh) {
    m_Meshes.push_back(iMesh);
}

} // namespace CodeHero

