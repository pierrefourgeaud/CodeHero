// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/shader.h"
#include "core/enginecontext.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"
#include "graphics/rendersystem.h"

namespace CodeHero {

void Shader::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Shader);

    CH_OBJECT_ATTRIBUTE(Shader, "File", std::string, Variant::Value::VVT_String, nullptr, &Shader::Load);
    CH_OBJECT_ATTRIBUTE(Shader, "Defines", VariantHashMap, Variant::Value::VVT_HashMap, nullptr, &Shader::SetDefines);
}

std::shared_ptr<Shader> Shader::Create(const std::shared_ptr<EngineContext>& iContext) {
    return iContext->GetSubsystem<RenderSystem>()->CreateShader();
}

}