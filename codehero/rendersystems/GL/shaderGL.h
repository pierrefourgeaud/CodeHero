// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_SHADERGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_SHADERGL_H_

#include <unordered_map>
#include "graphics/shader.h"
#include "core/errors.h"

namespace CodeHero {

class ShaderGL : public Shader {
public:
    ShaderGL();
    ~ShaderGL();

    Shader& Load(const std::string& iFilePath) override;
    Shader& SetDefines(const std::unordered_map<std::string, std::string>& iDefines) override;
    Shader& Compile() override;

private:
    bool m_IsLoaded = false;
    std::string m_ShaderFilePath;
    std::string m_ShaderCode;
    std::unordered_map<std::string, std::string> m_Defines;

    // Compilation methods
    Error _CreateShader();
    Error _AddDefinesToCode();
    Error _ReplaceIncludes(const std::string& iParentFile, const std::string& iShaderCode, std::string& oCode);
    Error _CompileShader(const std::string& iShaderCode);
};

}  // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_SHADERGL_H_
