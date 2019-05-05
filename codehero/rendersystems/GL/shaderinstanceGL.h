// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_RENDERSYSTEMS_GL_SHADERINSTANCEGL_H_
#define CODEHERO_RENDERSYSTEMS_GL_SHADERINSTANCEGL_H_

#include <unordered_map>
#include "core/errors.h"
#include "graphics/shaderinstance.h"

namespace CodeHero {

class ShaderInstanceGL : public ShaderInstance {
   public:
    explicit ShaderInstanceGL(const std::shared_ptr<EngineContext>& iContext);
    ~ShaderInstanceGL() override;

    Error Compile() override;

   private:
    // Compilation methods
    Error _CreateShader(const std::string& iFilePath);
    Error _AddDefinesToCode(std::string& ioCode);
    Error _ReplaceIncludes(const std::string& iParentFile,
                           const std::string& iShaderCode,
                           std::string& oCode);
    Error _CompileShader(const std::string& iShaderCode);
};

} // namespace CodeHero

#endif // CODEHERO_RENDERSYSTEMS_GL_SHADERINSTANCEGL_H_
