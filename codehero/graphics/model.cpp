// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/model.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"

namespace CodeHero {

Model::Model(const std::shared_ptr<EngineContext>& iContext)
    : Drawable(iContext, Drawable::DrawableType::DT_Geometry) {}

Model::~Model() {}

void Model::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Model);

    CH_OBJECT_ATTRIBUTE_CAST(Model, "Meshes", std::shared_ptr<Serializable>, Mesh, Variant::Value::VVT_SerializablePtr, nullptr, &Model::AddMesh);
}

std::shared_ptr<Model> Model::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Model>(iContext);
}

void Model::AddMesh(const std::shared_ptr<Mesh>& iMesh) {
    m_Meshes.push_back(iMesh);
}

} // namespace CodeHero

