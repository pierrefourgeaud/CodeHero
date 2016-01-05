// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <stdio.h>

#include "./shader.h"
#include "./logging/logger.h"

using namespace std;

namespace CodeHero {

Shader::Shader() {
    m_Program = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram(m_Program);
}

Shader& Shader::Attach(const string& iFilename) {
    std::string shaderCode = _GetShader(iFilename);

    GLuint shader = _CreateShader(iFilename);

    bool status = _CompileShader(shader, shaderCode);

    if (status) {
        glAttachShader(m_Program, shader);
        glDeleteShader(shader);
    }

    return *this;
}

Shader& Shader::Link() {
    glLinkProgram(m_Program);

    GLint success;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (success == false) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
        LOGE << "Shader program link failed." << endl << infoLog << endl;
    }

    return *this;
}

void Shader::Use() {
    glUseProgram(m_Program);
}

string Shader::_GetShader(const string& iShaderPath) {
    ifstream shaderFile;

    shaderFile.open(iShaderPath);

    stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}

GLuint Shader::_CreateShader(const string& iFilename) {
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
    return false;
}

bool Shader::_CompileShader(GLuint iShader, const string& iShaderCode) {
    const GLchar* shaderCode = iShaderCode.c_str();

    glShaderSource(iShader, 1, &shaderCode, nullptr);
    glCompileShader(iShader);

    GLint success;
    glGetShaderiv(iShader, GL_COMPILE_STATUS, &success);
    if (success == false) {
        GLchar infoLog[512];
        glGetShaderInfoLog(iShader, 512, nullptr, infoLog);
        LOGE << "Shader compilation failed." << endl << infoLog << endl;
    }

    return success;
}

}  // namespace CodeHero
