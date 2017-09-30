// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SHADER_H_
#define CODEHERO_GRAPHICS_SHADER_H_

#include <string>
#include <unordered_map>
#include "core/gpuobject.h"

namespace CodeHero {

// Forward declaration
class RenderSystem;

class Shader : public GPUObject {
public:
    Shader() {}
    virtual ~Shader() {}

    virtual Shader& Load(const std::string& iFilePath) = 0;
    virtual Shader& SetDefines(const std::unordered_map<std::string, std::string>& iDefines) = 0;
    virtual Shader& Compile() = 0;

    bool IsCompiled() const { return m_IsCompiled; }

protected:
    bool m_IsCompiled = false;
};

}  // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SHADER_H_