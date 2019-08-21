// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_TECHNIQUE_H_
#define CODEHERO_GRAPHICS_TECHNIQUE_H_

#include <map>
#include <string>
#include "core/serializable.h"
#include "graphics/rendersystem.h"
#include "graphics/shader.h"

namespace CodeHero {

// Forward declaration
class ShaderProgram;

class Technique : public Serializable {
    using ShaderDefines = std::map<std::string, std::string>;

   public:
    OBJECT(Technique, Serializable)

    Technique(const std::shared_ptr<EngineContext>& iContext) : Serializable(iContext) {}
    virtual ~Technique() {}

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Technique> Create(const std::shared_ptr<EngineContext>& iContext);

    std::shared_ptr<Shader> GetShader(const Shader::Type& iShaderType) const;
    void SetShader(const std::string& iShaderPath);
    void SetShader(const std::shared_ptr<Shader>& iShader);
    const ShaderDefines& GetShaderDefines(const Shader::Type& iShaderType) const;
    void SetShaderDefines(const Shader::Type& iShaderType, const ShaderDefines& iDefines);

    void SetBlendModes(bool iBlendEnabled,
                       const std::string& iSrcMode,
                       const std::string& iDstMode);
    bool IsBlendEnabled() const { return m_BlendEnabled; }
    BlendMode GetSrcBlendMode() const { return m_SrcMode; }
    BlendMode GetDstBlendMode() const { return m_DstMode; }

    void SetCachedShaderProgram(const std::shared_ptr<ShaderProgram>& iProgram);
    std::shared_ptr<ShaderProgram> GetCachedShaderProgram() const { return m_pCachedShaderProgram; }

   private:
    std::shared_ptr<Shader> m_pVtxShader;
    std::shared_ptr<Shader> m_pFragShader;
    ShaderDefines m_VtxShaderDefines;
    ShaderDefines m_FragShaderDefines;

    bool m_BlendEnabled = false;
    BlendMode m_SrcMode;
    BlendMode m_DstMode;

    // Cached shaderProgram: This is computer on the first rendering this technique will be used
    // for.
    std::shared_ptr<ShaderProgram> m_pCachedShaderProgram;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_TECHNIQUE_H_