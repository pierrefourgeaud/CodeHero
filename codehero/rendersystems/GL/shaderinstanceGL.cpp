// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "rendersystems/GL/shaderinstanceGL.h"

#include <logger.h>
#include "core/fileaccess.h"
#include "core/utils.h"
#include "graphics/shader.h"

#include <glad/glad.h>

namespace CodeHero {

ShaderInstanceGL::ShaderInstanceGL(const std::shared_ptr<EngineContext>& iContext)
    : ShaderInstance(iContext) {}

ShaderInstanceGL::~ShaderInstanceGL() {
    glDeleteShader(GetGPUObject().intHandle);
}

Error ShaderInstanceGL::Compile() {
    auto shader = m_pOwner.lock();
    if (!shader) {
        LOGE << "[ShaderInstanceGL]: Shader pointer expired. An instance cannot be created."
             << std::endl;
        return Error::FAILED;
    }

    if (!shader->IsLoaded()) {
        LOGE << "[ShaderInstanceGL]: Failed to compile - Shader is not loaded." << std::endl;
        return Error::ERR_NO_FILE_OPENED;
    }

    if (_CreateShader(shader->GetShaderPath()) != Error::OK) {
        LOGE << "[ShaderInstanceGL]: Failed to create shader object." << std::endl;
        return Error::ERR_COMPILATION_FAILED;
    }

    auto code = shader->GetShaderCode();
    if (_AddDefinesToCode(code) != Error::OK) {
        LOGE << "[ShaderInstanceGL]: Failed to add the defines to shader." << std::endl;
        return Error::ERR_COMPILATION_FAILED;
    }

    std::string finalCode;
    if (_ReplaceIncludes(shader->GetShaderPath(), code, finalCode) != Error::OK) {
        LOGE << "[ShaderInstanceGL]: Failed to replace #includes." << std::endl;
        return Error::ERR_COMPILATION_FAILED;
    }

    if (_CompileShader(finalCode) != Error::OK) {
        LOGE << "[ShaderInstanceGL]: Failed to compile shader." << std::endl;
        return Error::ERR_COMPILATION_FAILED;
    }
    m_IsCompiled = true;

    return Error::OK;
}

Error ShaderInstanceGL::_CreateShader(const std::string& iFilePath) {
    auto index = iFilePath.rfind(".");
    auto ext = iFilePath.substr(index + 1);
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
// To achieve that, we split the shader per line and pass all empty lines and the line with
// #version.
Error ShaderInstanceGL::_AddDefinesToCode(std::string& ioCode) {
    if (!m_Defines.empty()) {
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
        for (const auto& el : m_Defines) {
            defines += "#define " + el.first + ' ' + el.second + '\n';
        }
        sources.insert(sources.begin() + i, defines);

        // Put everything back together
        ioCode = Join(sources, '\n');
    }

    return Error::OK;
}

Error ShaderInstanceGL::_ReplaceIncludes(const std::string& iParentFile,
                                         const std::string& iShaderCode,
                                         std::string& oCode) {
    std::string::size_type posInclude = iShaderCode.find("#include ");
    oCode += iShaderCode.substr(0, posInclude);
    while (posInclude != std::string::npos) {
        std::string::size_type startPos = iShaderCode.find("\"", posInclude);
        if (startPos == std::string::npos) {
            LOGE << "[ShaderInstanceGL]: Replace #includes failed with missing opening '\"'."
                 << std::endl;
            return Error::ERR_PARSING_FAILED;
        }

        std::string::size_type endPos = iShaderCode.find("\"", startPos + 1);
        if (endPos == std::string::npos) {
            LOGE << "[ShaderInstanceGL]: Replace #includes failed with missing closing '\"'."
                 << std::endl;
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
            LOGE << "[ShaderInstanceGL]: Replace #includes failed with '" << filePath
                 << "' not found'." << std::endl;
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

Error ShaderInstanceGL::_CompileShader(const std::string& iShaderCode) {
    const GLchar* shaderCode = iShaderCode.c_str();

    glShaderSource(GetGPUObject().intHandle, 1, &shaderCode, nullptr);
    glCompileShader(GetGPUObject().intHandle);

    GLint success;
    glGetShaderiv(GetGPUObject().intHandle, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLchar infoLog[512];
        glGetShaderInfoLog(GetGPUObject().intHandle, 512, nullptr, infoLog);
        LOGE << "[ShaderInstanceGL]: Compilation failed with " << infoLog << std::endl;
        return Error::ERR_COMPILATION_FAILED;
    }

    return Error::OK;
}

} // namespace CodeHero