// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SHADER_H_
#define CODEHERO_GRAPHICS_SHADER_H_

#include <map>
#include <string>
#include <unordered_map>
#include "core/errors.h"
#include "core/serializable.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class ShaderInstance;

class Shader : public Serializable, public std::enable_shared_from_this<Shader> {
   public:
    enum Type : uint8_t { T_Vertex = 0, T_Fragment };

    OBJECT(Shader, Serializable)

    Shader(const std::shared_ptr<EngineContext>& iContext) : Serializable(iContext) {}
    virtual ~Shader() {}

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Shader> Create(const std::shared_ptr<EngineContext>& iContext);

    Error Load(const std::string& iFilePath);

    Type GetType() const { return m_Type; }
    bool IsLoaded() const { return m_IsLoaded; }
    const std::string& GetShaderPath() const { return m_ShaderFilePath; }
    const std::string& GetShaderCode() const { return m_ShaderCode; }
    std::shared_ptr<ShaderInstance> GetInstance(const std::map<std::string, std::string>& iDefines);

   private:
    Type m_Type;
    bool m_IsLoaded = false;
    std::string m_ShaderFilePath;
    std::string m_ShaderCode;

    std::unordered_map<std::string, std::shared_ptr<ShaderInstance>> m_Instances;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SHADER_H_