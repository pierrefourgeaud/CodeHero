// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_SHADER_H_
#define CODEHERO_CORE_SHADER_H_

#include <string>
#include <unordered_map>
#include "core/gpuobject.h"

namespace CodeHero {

// Forward declaration
class RenderSystem;

class Shader : public GPUObject {
public:
    Shader(RenderSystem& iRenderSystem) : m_rRenderSystem(iRenderSystem) {}
    virtual ~Shader() {}

    virtual Shader& Attach(const std::string& iFilename, const std::unordered_map<std::string, std::string>& iDefines = {}) = 0;
    virtual Shader& Link() = 0;

    virtual void Use() = 0;

protected:
    RenderSystem& m_rRenderSystem;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_SHADER_H_
