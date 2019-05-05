// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/shader.h"
#include "core/enginecontext.h"
#include "core/fileaccess.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"
#include "core/utils.h"
#include "graphics/rendersystem.h"
#include "graphics/shaderinstance.h"

namespace CodeHero {

// TODO(pierre) We should reflect on this utils. Should we keep it here or put it in a "stringutils" file ?
std::string Join(const std::map<std::string, std::string>& iInput) {
    std::string result;
    for (const auto& def : iInput) {
        result += def.first;
        result += def.second;
    }

    return result;
}

void Shader::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Shader);

    CH_OBJECT_ATTRIBUTE(Shader, "File", std::string, Variant::Value::VVT_String, nullptr, &Shader::Load);
}

std::shared_ptr<Shader> Shader::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Shader>(iContext);
}

Error Shader::Load(const std::string& iFilePath) {
    FileAccess file;
    if (file.Open(iFilePath, FileAccess::READ) != Error::OK) {
        LOGE << "[Shader]: Failed to load " << iFilePath << std::endl;
        return Error::ERR_CANT_OPEN;
    }

    m_ShaderCode = file.ReadAll();
    file.Close();
    m_IsLoaded = true;
    m_ShaderFilePath = iFilePath;

    // We still need to load the type
    if (EndsWith(iFilePath, ".vert")) {
        m_Type = T_Vertex;
    } else if (EndsWith(iFilePath, ".frag")) {
        m_Type = T_Fragment;
    } else {
        // We should not get here
        CH_ASSERT(false);
        return Error::FAILED;
    }

    return Error::OK;
}

std::shared_ptr<ShaderInstance> Shader::GetInstance(const std::map<std::string, std::string>& iDefines) {
    CH_ASSERT(m_IsLoaded);

    if (!m_IsLoaded) {
        return nullptr;
    }

    auto definesKey = Join(iDefines);
    auto instance = m_Instances.find(definesKey);
    if (instance == m_Instances.end()) {
        auto shaderInstance = m_pContext->GetSubsystem<RenderSystem>()->CreateShaderInstance();
        shaderInstance->SetOwner(shared_from_this());
        shaderInstance->SetDefines(std::move(iDefines));
        if (Error::OK != shaderInstance->Compile()) {
            LOGE << "[Shader]: Failed to compile instance of shader: '" << m_ShaderFilePath << "'." << std::endl;
            return nullptr;
        }

        m_Instances[definesKey] = shaderInstance;
        return shaderInstance;
    } else {
        return instance->second;
    }
}

}