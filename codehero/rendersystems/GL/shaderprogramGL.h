// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_SHADERPROGRAMGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_SHADERPROGRAMGL_H_

#include <glad/glad.h>
#include <unordered_map>

#include "core/errors.h"
#include "graphics/shaderprogram.h"

namespace CodeHero {

struct ShaderParameter {
    int location;
    unsigned int type;
};

class ShaderProgramGL : public ShaderProgram {
public:
    ShaderProgramGL(const std::shared_ptr<EngineContext>& iContext);
    ~ShaderProgramGL();

    ShaderProgram& Attach(const std::shared_ptr<ShaderInstance>& iShader) override;
    ShaderProgram& Link() override;

    void Use() override;

    bool HasParameter(const std::string& iParamName);
    const ShaderParameter& GetParameter(const std::string& iParamName);

private:
    void _ParseParameters();

    std::unordered_map<std::string, ShaderParameter> m_Parameters;
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_SHADERPROGRAMGL_H_
