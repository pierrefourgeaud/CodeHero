// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_SHADERPROGRAMGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_SHADERPROGRAMGL_H_

#include <glad/glad.h>
#include <unordered_map>
#include "graphics/shaderprogram.h"
#include "core/errors.h"

namespace CodeHero {

struct ShaderParameter {
    int location;
    unsigned int type;
};

class ShaderProgramGL : public ShaderProgram {
public:
    ShaderProgramGL(RenderSystem& iRenderSystem);
    ~ShaderProgramGL();

    ShaderProgram& Attach(const std::string& iFilename, const std::unordered_map<std::string, std::string>& iDefines = {}) override;
    ShaderProgram& Link() override;

    void Use() override;

    bool HasParameter(const std::string& iParamName);
    const ShaderParameter& GetParameter(const std::string& iParamName);

private:
    std::string _GetShader(const std::string& iShaderPath);
    GLuint _CreateShader(const std::string& iCode);
    bool _CompileShader(GLuint iShader, const std::string& iShaderCode);
    void _ParseParameters();

    Error _AddDefines(std::string& ioCode, const std::unordered_map<std::string, std::string>& iDefines);
    Error _ReplaceIncludes(const std::string& iParentFile, const std::string& iSourceCode, std::string& oCode);

    std::unordered_map<std::string, ShaderParameter> m_Parameters;
};

}  // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_SHADERPROGRAMGL_H_
