// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <exception>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <stdio.h>

#include "graphics/rendersystem.h"
#include "rendersystems/GL/shaderGL.h"
#include <logger.h>

using namespace std;

namespace CodeHero {

ShaderGL::ShaderGL(RenderSystem& iRenderSystem)
    : Shader(iRenderSystem) {
    _SetGPUObject(glCreateProgram());
}

ShaderGL::~ShaderGL() {
    glDeleteProgram(GetGPUObject().intHandle);
}

Shader& ShaderGL::Attach(const string& iFilename) {
    std::string shaderCode = _GetShader(iFilename);

    GLuint shader = _CreateShader(iFilename);

    bool status = _CompileShader(shader, shaderCode);

    if (status) {
        glAttachShader(GetGPUObject().intHandle, shader);
        glDeleteShader(shader);
    }

    return *this;
}

Shader& ShaderGL::Link() {
    glLinkProgram(GetGPUObject().intHandle);

    GLint success;
    glGetProgramiv(GetGPUObject().intHandle, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLchar infoLog[512];
        glGetProgramInfoLog(GetGPUObject().intHandle, 512, nullptr, infoLog);
        LOGE << "Shader program link failed." << endl << infoLog << endl;
    }

    _ParseParameters();

    return *this;
}

void ShaderGL::Use() {
    glUseProgram(GetGPUObject().intHandle);

    m_rRenderSystem.SetShaderProgramInUse(this);
}

bool ShaderGL::HasParameter(const std::string& iParamName) {
    return m_Parameters.find(iParamName) != m_Parameters.end();
}

const ShaderParameter& ShaderGL::GetParameter(const std::string& iParamName) {
    auto param = m_Parameters.find(iParamName);
    if (param == m_Parameters.end()) {
        throw std::range_error("Parameter " + iParamName + " does not exists.");
    }

    return param->second;
}

string ShaderGL::_GetShader(const string& iShaderPath) {
    ifstream shaderFile;

    shaderFile.open(iShaderPath);

    stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}

GLuint ShaderGL::_CreateShader(const string& iFilename) {
    auto index = iFilename.rfind(".");
    auto ext = iFilename.substr(index + 1);
    if (ext == "comp") {
        return glCreateShader(GL_COMPUTE_SHADER);
    } else if (ext == "frag") {
        return glCreateShader(GL_FRAGMENT_SHADER);
    } else if (ext == "geom") {
        return glCreateShader(GL_GEOMETRY_SHADER);
    } else if (ext == "vert") {
        return glCreateShader(GL_VERTEX_SHADER);
    }
    return 0;
}

bool ShaderGL::_CompileShader(GLuint iShader, const string& iShaderCode) {
    const GLchar* shaderCode = iShaderCode.c_str();

    glShaderSource(iShader, 1, &shaderCode, nullptr);
    glCompileShader(iShader);

    GLint success;
    glGetShaderiv(iShader, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLchar infoLog[512];
        glGetShaderInfoLog(iShader, 512, nullptr, infoLog);
        LOGE << "Shader compilation failed." << endl << infoLog << endl;
    }

    return success != 0;
}

void ShaderGL::_ParseParameters() {
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
        m_Parameters[uniformName] = {location, type};
    }
}

}  // namespace CodeHero
