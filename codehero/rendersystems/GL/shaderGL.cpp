// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <exception>
#include <string>

#include <stdio.h>

#include "core/fileaccess.h"
#include "core/utils.h"
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

Shader& ShaderGL::Attach(const string& iFilename, const std::unordered_map<std::string, std::string>& iDefines/* = {}*/) {
    std::string shaderCode = _GetShader(iFilename);

    GLuint shader = _CreateShader(iFilename);

    if (_AddDefines(shaderCode, iDefines) != Error::OK) {
        LOGE << "Shader compile error: Failed to add the defines to shader." << std::endl;
        return *this;
    }

    std::string finalCode;
    if (_ReplaceIncludes(iFilename, shaderCode, finalCode) != Error::OK) {
        LOGE << "Shader compile error: Failed to replace #includes." << std::endl;
        return *this;
    }

    bool status = _CompileShader(shader, finalCode);

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
    // TODO(pierre) Implement error checking here
    FileAccess file;
    file.Open(iShaderPath, FileAccess::READ);

    std::string content = file.ReadAll();
    file.Close();

    return std::move(content);
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

// The defines shall be placed as early as possible (in case of early use) but must be placed
// after the `#version ...` statement
// To achieve that, we split the shader per line and pass all empty lines and the line with #version.
Error ShaderGL::_AddDefines(std::string& ioCode, const std::unordered_map<std::string, std::string>& iDefines) {
    if (!iDefines.empty()) {
        // Split the lines by '\n'
        std::vector<std::string> sources = Split(ioCode, '\n');

        // Search for the first position to add the defines
        size_t sizeSources = sources.size();
        size_t i;
        for (i = 0; i < sizeSources; ++i) {
            Trim(sources[i]);
            if (!sources[i].empty() && !StartsWith(sources[i], "#version ")) {
                break;
            }
        }

        // Add the defines
        std::string defines;
        for (const auto& el : iDefines) {
            defines += "#define " + el.first + ' ' + el.second + '\n';
        }
        sources.insert(sources.begin() + i, defines);

        // Put everything back together
        ioCode = Join(sources, '\n');
    }

    return Error::OK;
}

Error ShaderGL::_ReplaceIncludes(const std::string& iParentFile, const std::string& iShaderCode, std::string& oCode) {
    std::string::size_type posInclude = iShaderCode.find("#include ");
    oCode += iShaderCode.substr(0, posInclude);
    while (posInclude != std::string::npos) {
        std::string::size_type startPos = iShaderCode.find("\"", posInclude);
        if (startPos == std::string::npos) {
            LOGE << "Shader replace include failed: Missing opening '\"'." << std::endl;
            return Error::ERR_PARSING_FAILED;
        }

        std::string::size_type endPos = iShaderCode.find("\"", startPos + 1);
        if (endPos == std::string::npos) {
            LOGE << "Shader replace include failed: Missing closing '\"'." << std::endl;
            return Error::ERR_PARSING_FAILED;
        }
        
        startPos++;
        std::string filename = iShaderCode.substr(startPos, endPos - startPos);
        std::string filePath = iParentFile.substr(0, iParentFile.rfind("/"));
        if (filePath == iParentFile) {
            filePath = "";
        }
        filePath += "/" + filename;
        FileAccess file;
        if (file.Open(filePath, FileAccess::READ) != Error::OK) {
            // TODO(pierre) return proper error
            LOGE << "Shader replace include failed: '" << filePath << "' not found'." << std::endl;
            return Error::ERR_FILE_NOT_FOUND;
        }
        std::string content = file.ReadAll();
        file.Close();
        // Recurse to do the same operation in the included file.
        Error err;
        if ((err = _ReplaceIncludes(filePath, content, oCode)) != Error::OK) {
            return err;
        }
        posInclude = iShaderCode.find("#include ", endPos);
        oCode += iShaderCode.substr(endPos + 1, posInclude);
    }

    return Error::OK;
}

}  // namespace CodeHero
