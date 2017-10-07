// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/shaderprogram.h"
#include "core/enginecontext.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"
#include "graphics/rendersystem.h"
#include "graphics/shader.h"

namespace CodeHero {

void ShaderProgram::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(ShaderProgram);

    CH_OBJECT_ATTRIBUTE_CAST(ShaderProgram, "Shader", std::shared_ptr<Serializable>, Shader, Variant::Value::VVT_SerializablePtr, nullptr, &ShaderProgram::Attach);
}

std::shared_ptr<ShaderProgram> ShaderProgram::Create(const std::shared_ptr<EngineContext>& iContext) {
    return iContext->GetSubsystem<RenderSystem>()->CreateShaderProgram();
}

}