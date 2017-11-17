// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/technique.h"
#include "core/assert.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"

namespace CodeHero {

void Technique::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Technique);

    // TODO(pierre) This attribute doesn't offer any check on the validity that the shader passed is really vertex
    CH_OBJECT_ATTRIBUTE(Technique, "VertexShader", std::string, Variant::Value::VVT_String, nullptr, static_cast<void(Technique::*)(const std::string&)>(&Technique::SetShader));
    CH_OBJECT_ATTRIBUTE_CUSTOM(Technique, "VertexDefines", VariantHashMap, Variant::Value::VVT_HashMap, nullptr, [](Technique* iPtr, const VariantHashMap& iDefines) {
        iPtr->SetShaderDefines(Shader::T_Vertex, iDefines);
    });
    // TODO(pierre) This attribute doesn't offer any check on the validity that the shader passed is really fragment
    CH_OBJECT_ATTRIBUTE(Technique, "FragmentShader", std::string, Variant::Value::VVT_String, nullptr, static_cast<void(Technique::*)(const std::string&)>(&Technique::SetShader));
    CH_OBJECT_ATTRIBUTE_CUSTOM(Technique, "FragmentDefines", VariantHashMap, Variant::Value::VVT_HashMap, nullptr, [](Technique* iPtr, const VariantHashMap& iDefines) {
        iPtr->SetShaderDefines(Shader::T_Fragment, iDefines);
    });
}

std::shared_ptr<Technique> Technique::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Technique>(iContext);
}

std::shared_ptr<Shader> Technique::GetShader(const Shader::Type& iType) const {
    switch (iType) {
    case Shader::T_Vertex: return m_pVtxShader;
    case Shader::T_Fragment: return m_pFragShader;
    default:
        // We should never be here
        CH_ASSERT(false);
        return nullptr;
    }
}

void Technique::SetShader(const std::string& iShaderPath) {
    auto shader = std::make_shared<Shader>(m_pContext);

    shader->Load(iShaderPath);
    SetShader(shader);
}

void Technique::SetShader(const std::shared_ptr<Shader>& iShader) {
    switch (iShader->GetType()) {
    case Shader::T_Vertex:
        m_pVtxShader = iShader;
        break;
    case Shader::T_Fragment:
        m_pFragShader = iShader;
        break;
    default:
        // We should never be here
        CH_ASSERT(false);
        break;
    }

    if (m_pCachedShaderProgram) {
        m_pCachedShaderProgram.reset();
    }
}

const Technique::ShaderDefines& Technique::GetShaderDefines(const Shader::Type& iType) const {
    switch (iType) {
    case Shader::T_Vertex: return m_VtxShaderDefines;
    case Shader::T_Fragment: return m_FragShaderDefines;
    default:
        // We should never be here
        CH_ASSERT(false);
        // Default to vtxdefines
        return m_VtxShaderDefines;
    }
}

void Technique::SetShaderDefines(const Shader::Type& iShaderType, const ShaderDefines& iDefines) {
    switch (iShaderType) {
    case Shader::T_Vertex:
        m_VtxShaderDefines = iDefines;
        break;
    case Shader::T_Fragment:
        m_FragShaderDefines = iDefines;
        break;
    default:
        // We should never be here
        CH_ASSERT(false);
        break;
    }

    if (m_pCachedShaderProgram) {
        m_pCachedShaderProgram.reset();
    }
}

void Technique::SetCachedShaderProgram(const std::shared_ptr<ShaderProgram>& iProgram) {
    CH_ASSERT(m_pCachedShaderProgram == nullptr);

    m_pCachedShaderProgram = iProgram;
}

} // namespace CodeHero