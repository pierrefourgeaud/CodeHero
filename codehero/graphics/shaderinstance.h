// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SHADERINSTANCE_H_
#define CODEHERO_GRAPHICS_SHADERINSTANCE_H_

#include <map>
#include "core/errors.h"
#include "core/gpuobject.h"
#include "core/serializable.h"

namespace CodeHero {

// Forward declaration
class Shader;

class ShaderInstance : public Serializable, public GPUObject {
public:
    OBJECT(ShaderInstance, Serializable)

    explicit ShaderInstance(const std::shared_ptr<EngineContext>& iContext)
        : Serializable(iContext) {}
    virtual ~ShaderInstance() {}

    void SetOwner(const std::shared_ptr<Shader>& iOwner);
    void SetDefines(const std::map<std::string, std::string>&& iDefines);

    virtual Error Compile() = 0;

    bool IsCompiled() const { return m_IsCompiled; }

protected:
    bool m_IsCompiled = false;

    std::weak_ptr<Shader> m_pOwner;
    std::map<std::string, std::string> m_Defines;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SHADERINSTANCE_H_