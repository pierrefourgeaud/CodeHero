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
class ShaderInstance;

class ShaderProgram : public Object, public GPUObject {
public:
    OBJECT(ShaderProgram, Object)

    ShaderProgram(const std::shared_ptr<EngineContext>& iContext) : Object(iContext) {}
    virtual ~ShaderProgram() {}

    virtual ShaderProgram& Attach(const std::shared_ptr<ShaderInstance>& iShader) = 0;
    virtual ShaderProgram& Link() = 0;

    virtual void Use() = 0;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SHADERPROGRAM_H_