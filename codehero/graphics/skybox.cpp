// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/skybox.h"
#include "core/type_traits/attributeaccessor_impl.h"
#include "core/type_traits/objectdefinition.h"
#include "graphics/cube.h"
#include "graphics/material.h"

namespace CodeHero {

Skybox::Skybox(const std::shared_ptr<EngineContext>& iContext)
    : Model(iContext) {}

Skybox::~Skybox() {}

void Skybox::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Skybox);

    CH_OBJECT_ATTRIBUTE_CAST(Skybox, "Material", std::shared_ptr<Serializable>, Material, Variant::Value::VVT_SerializablePtr, nullptr, &Skybox::Initialize);
}

std::shared_ptr<Skybox> Skybox::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Skybox>(iContext);
}

void Skybox::Initialize(const std::shared_ptr<Material>& iMaterial) {
    auto mesh = std::make_shared<Cube>(m_pContext);
    mesh->SetMaterial(iMaterial);
    m_Meshes.push_back(mesh);
}

} // namespace CodeHero