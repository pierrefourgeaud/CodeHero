// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "rendersystems/GL/shaderGL.h"
#include <glad/glad.h>
#include <logger.h>
#include "core/fileaccess.h"
#include "core/utils.h"

namespace CodeHero {

ShaderGL::ShaderGL(const std::shared_ptr<EngineContext>& iContext)
    : Shader(iContext) {}

ShaderGL::~ShaderGL() {
    glDeleteShader(GetGPUObject().intHandle);
}

Shader& ShaderGL::Load(const std::string& iFilePath) {
    FileAccess file;
    if (file.Open(iFilePath, FileAccess::READ) != Error::OK) {
        LOGE << "[ShaderGL]: Faile to load " << iFilePath << std::endl;
        return *this;
    }

    m_ShaderCode = file.ReadAll();
    file.Close();
    m_IsLoaded = true;
    m_ShaderFilePath = iFilePath;

    return *this;
}

Shader& ShaderGL::SetDefines(const std::unordered_map<std::string, std::string>& iDefines) {
    m_Defines = iDefines;
    return *this;
}

Shader& ShaderGL::Compile() {
    if (!m_IsLoaded) {
        LOGE << "[ShaderGL]: Failed to compile - Shader is not loaded." << std::endl;
        return *this;
    }

    if (_CreateShader() != Error::OK) {
        LOGE << "[ShaderGL]: Failed to create shader object, shader not loaded." << std::endl;
        return *this;
    }

    if (_AddDefinesToCode() != Error::OK) {
        LOGE << "[ShaderGL]: Failed to add the defines to shader." << std::endl;
        return *this;
    }

    std::string finalCode;
    if (_ReplaceIncludes(m_ShaderFilePath, m_ShaderCode, finalCode) != Error::OK) {
        LOGE << "[ShaderGL]: Failed to replace #includes." << std::endl;
        return *this;
    }

    if (_CompileShader(finalCode) != Error::OK) {
        LOGE << "[ShaderGL]: Failed to compile shader." << std::endl;
        return *this;
    }
    m_IsCompiled = true;

    return *this;
}

Error ShaderGL::_CreateShader() {
    auto index = m_ShaderFilePath.rfind(".");
    auto ext = m_ShaderFilePath.substr(index + 1);
    GLuint shader = 0;
    if (ext == "comp") {
        shader = glCreateShader(GL_COMPUTE_SHADER);
    } else if (ext == "frag") {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    } else if (ext == "geom") {
        shader = glCreateShader(GL_GEOMETRY_SHADER);
    } else if (ext == "vert") {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }

    if (shader != 0) {
        _SetGPUObject(shader);
        return Error::OK;
    } else {
        return Error::FAILED;
    }
}

// The defines shall be placed as early as possible (in case of early use) but must be placed
// after the `#version ...` statement
// To achieve that, we split the shader per line and pass all empty lines and the line with #version.
Error ShaderGL::_AddDefinesToCode() {
    if (!m_Defines.empty()) {
        // Split the lines by '\n'
        std::vector<std::string> sources = Split(m_ShaderCode, '\n');

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
        for (const auto& el : m_Defines) {
            defines += "#define " + el.first + ' ' + el.second + '\n';
        }
        sources.insert(sources.begin() + i, defines);

        // Put everything back together
        m_ShaderCode = Join(sources, '\n');
    }

    return Error::OK;
}

Error ShaderGL::_ReplaceIncludes(const std::string& iParentFile, const std::string& iShaderCode, std::string& oCode) {
    std::string::size_type posInclude = iShaderCode.find("#include ");
    oCode += iShaderCode.substr(0, posInclude);
    while (posInclude != std::string::npos) {
        std::string::size_type startPos = iShaderCode.find("\"", posInclude);
        if (startPos == std::string::npos) {
            LOGE << "[ShaderGL]: Replace #includes failed with missing opening '\"'." << std::endl;
            return Error::ERR_PARSING_FAILED;
        }

        std::string::size_type endPos = iShaderCode.find("\"", startPos + 1);
        if (endPos == std::string::npos) {
            LOGE << "[ShaderGL]: Replace #includes failed with missing closing '\"'." << std::endl;
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
            LOGE << "[ShaderGL: Replace #includes failed with '" << filePath << "' not found'." << std::endl;
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

Error ShaderGL::_CompileShader(const std::string& iShaderCode) {
    const GLchar* shaderCode = iShaderCode.c_str();

    glShaderSource(GetGPUObject().intHandle, 1, &shaderCode, nullptr);
    glCompileShader(GetGPUObject().intHandle);

    GLint success;
    glGetShaderiv(GetGPUObject().intHandle, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLchar infoLog[512];
        glGetShaderInfoLog(GetGPUObject().intHandle, 512, nullptr, infoLog);
        LOGE << "[ShaderGL]: Compilation failed with " << infoLog << std::endl;
        return Error::ERR_COMPILATION_FAILED;
    }

    return Error::OK;
}

} // namespace CodeHero