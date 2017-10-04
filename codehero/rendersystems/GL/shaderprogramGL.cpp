// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <exception>
#include <string>
#include "core/assert.h"
#include "core/enginecontext.h"
#include "graphics/shader.h"
#include "graphics/rendersystem.h"
#include "rendersystems/GL/shaderprogramGL.h"
#include <logger.h>

namespace CodeHero {

ShaderProgramGL::ShaderProgramGL(const std::shared_ptr<EngineContext>& iContext)
    : ShaderProgram(iContext) {
    _SetGPUObject(glCreateProgram());
}

ShaderProgramGL::~ShaderProgramGL() {
    glDeleteProgram(GetGPUObject().intHandle);
}

ShaderProgram& ShaderProgramGL::Attach(const std::shared_ptr<Shader>& iShader) {
    CH_ASSERT(iShader != nullptr);

    if (iShader->IsCompiled()) {
        glAttachShader(GetGPUObject().intHandle, iShader->GetGPUObject().intHandle);
    }

    return *this;
}

ShaderProgram& ShaderProgramGL::Link() {
    glLinkProgram(GetGPUObject().intHandle);

    GLint success;
    glGetProgramiv(GetGPUObject().intHandle, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLchar infoLog[512];
        glGetProgramInfoLog(GetGPUObject().intHandle, 512, nullptr, infoLog);
        LOGE << "[ShaderProgramGL]: Link failed with " << infoLog << std::endl;
    }

    _ParseParameters();

    return *this;
}

void ShaderProgramGL::Use() {
    glUseProgram(GetGPUObject().intHandle);

    m_pContext->GetSubsystem<RenderSystem>()->SetShaderProgramInUse(this);
}

bool ShaderProgramGL::HasParameter(const std::string& iParamName) {
    return m_Parameters.find(iParamName) != m_Parameters.end();
}

const ShaderParameter& ShaderProgramGL::GetParameter(const std::string& iParamName) {
    auto param = m_Parameters.find(iParamName);
    if (param == m_Parameters.end()) {
        throw std::range_error("Parameter " + iParamName + " does not exists.");
    }

    return param->second;
}

void ShaderProgramGL::_ParseParameters() {
    const int MAX_PARAMETER_NAME_LENGTH = 256;
    char uniformName[MAX_PARAMETER_NAME_LENGTH];
    int uniformCount;

    glUseProgram(GetGPUObject().intHandle);
    glGetProgramiv(GetGPUObject().intHandle, GL_ACTIVE_UNIFORMS, &uniformCount);

    for (int i = 0; i < uniformCount; ++i) {
        unsigned int type;
        int count;

        glGetActiveUniform(GetGPUObject().intHandle, (GLuint)i, MAX_PARAMETER_NAME_LENGTH, 0, &count, &type, uniformName);
        int location = glGetUniformLocation(GetGPUObject().intHandle, uniformName);
        // We need to do some processing here if needed for array
        std::string name(uniformName);
        auto index = name.find("[");
        if (index != std::string::npos) {
            if (name.find("[0]", index) != std::string::npos) {
                m_Parameters[name.substr(0, index)] = {location, type};
            }
        }
        m_Parameters[uniformName] = {location, type};
    }
}

}  // namespace CodeHero
