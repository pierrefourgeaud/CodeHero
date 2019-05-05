// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/enginecontext.h"
#include "core/system.h"

namespace CodeHero {

void EngineContext::RegisterSubsystem(System* iSystem) {
    m_SubSystems[iSystem->GetTypeName()] = std::unique_ptr<System>(iSystem);
}

System* EngineContext::GetSubsystem(const std::string& iSystemName) {
    auto found = m_SubSystems.find(iSystemName);
    if (found == m_SubSystems.end()) {
        return nullptr;
    }

    return found->second.get();
}

} // namespace CodeHero
