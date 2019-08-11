// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "rendersystems/GL/shaderprogramGL.h"

#include <exception>
#include <string>

#include "core/assert.h"
#include "core/enginecontext.h"
#include "graphics/rendersystem.h"
#include "graphics/shaderinstance.h"
#include "rendersystems/GL/utils.h"

namespace CodeHero {

ShaderProgramGL::ShaderProgramGL(const std::shared_ptr<EngineContext>& iContext)
    : ShaderProgram(iContext) {
    unsigned int id;
    CH_GL_CALL_RET(id, glCreateProgram());
    _SetGPUObject(id);
}

ShaderProgramGL::~ShaderProgramGL() {
    CH_GL_CALL(glDeleteProgram(GetGPUObject().intHandle));
}

ShaderProgram& ShaderProgramGL::Attach(const std::shared_ptr<ShaderInstance>& iShader) {
    CH_ASSERT(iShader != nullptr);

    if (iShader->IsCompiled()) {
        CH_GL_CALL(glAttachShader(GetGPUObject().intHandle, iShader->GetGPUObject().intHandle));
    }

    return *this;
}

ShaderProgram& ShaderProgramGL::Link() {
    CH_GL_CALL(glLinkProgram(GetGPUObject().intHandle));

    GLint success;
    CH_GL_CALL(glGetProgramiv(GetGPUObject().intHandle, GL_LINK_STATUS, &success));
    if (success == 0) {
        GLchar infoLog[512];
        CH_GL_CALL(glGetProgramInfoLog(GetGPUObject().intHandle, 512, nullptr, infoLog));
        LOGE << "[ShaderProgramGL]: Link failed with " << infoLog << std::endl;
    }

    _ParseParameters();

    return *this;
}

void ShaderProgramGL::Use() {
    CH_GL_CALL(glUseProgram(GetGPUObject().intHandle));

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

    CH_GL_CALL(glUseProgram(GetGPUObject().intHandle));
    CH_GL_CALL(glGetProgramiv(GetGPUObject().intHandle, GL_ACTIVE_UNIFORMS, &uniformCount));

    for (int i = 0; i < uniformCount; ++i) {
        unsigned int type;
        int count;

        CH_GL_CALL(glGetActiveUniform(GetGPUObject().intHandle, (GLuint)i,
                                      MAX_PARAMETER_NAME_LENGTH, 0, &count, &type, uniformName));
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

} // namespace CodeHero
