// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SHADERPROGRAM_H_
#define CODEHERO_GRAPHICS_SHADERPROGRAM_H_

#include <string>
#include "core/gpuobject.h"
#include "core/serializable.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Shader;

class ShaderProgram : public Serializable, public GPUObject {
public:
    OBJECT(ShaderProgram, Serializable)

    ShaderProgram(const std::shared_ptr<EngineContext>& iContext)
        : Serializable(iContext) {}
    virtual ~ShaderProgram() {}

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<ShaderProgram> Create(const std::shared_ptr<EngineContext>& iContext);

    void EndLoad() override { Link(); }

    virtual ShaderProgram& Attach(const std::shared_ptr<Shader>& iShader) = 0;
    virtual ShaderProgram& Link() = 0;

    virtual void Use() = 0;
};

}  // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SHADERPROGRAM_H_