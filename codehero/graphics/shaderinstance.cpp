// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/shaderinstance.h"
#include "core/assert.h"

namespace CodeHero {

void ShaderInstance::SetOwner(const std::shared_ptr<Shader>& iOwner) {
    CH_ASSERT(iOwner);

    m_pOwner = iOwner;
}

void ShaderInstance::SetDefines(const std::map<std::string, std::string>&& iDefines) {
    m_Defines = std::move(iDefines);
}

} // namespace CodeHero