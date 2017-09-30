// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SHADERPROGRAM_H_
#define CODEHERO_GRAPHICS_SHADERPROGRAM_H_

#include <string>
#include "core/gpuobject.h"

namespace CodeHero {

// Forward declaration
class RenderSystem;
class Shader;

class ShaderProgram : public GPUObject {
public:
    ShaderProgram(RenderSystem& iRenderSystem) : m_rRenderSystem(iRenderSystem) {}
    virtual ~ShaderProgram() {}

    virtual ShaderProgram& Attach(const std::shared_ptr<Shader>& iShader) = 0;
    virtual ShaderProgram& Link() = 0;

    virtual void Use() = 0;

protected:
    RenderSystem& m_rRenderSystem;
};

}  // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SHADERPROGRAM_H_