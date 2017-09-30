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

    ShaderProgram& Attach(const std::shared_ptr<Shader>& iShader) override;
    ShaderProgram& Link() override;

    void Use() override;

    bool HasParameter(const std::string& iParamName);
    const ShaderParameter& GetParameter(const std::string& iParamName);

private:
    void _ParseParameters();

    std::unordered_map<std::string, ShaderParameter> m_Parameters;
};

}  // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_SHADERPROGRAMGL_H_
