// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <logger.h>
#include "graphics/rendersystem.h"

namespace CodeHero {

void RenderSystem::RegisterViewport(Viewport* iViewport) {
    m_RegisteredViewports.push_back(iViewport);
}

void RenderSystem::Render() {
    if (!m_pActiveViewport && m_RegisteredViewports.empty()) {
        LOGW << "RenderSystem: There is no viewport to render to." << std::endl;
        return;
    }

    if (!m_RegisteredViewports.empty()) {
        size_t size = m_RegisteredViewports.size();
        for (size_t i = 0; i < size; ++i) {
            SetViewport(m_RegisteredViewports[i]);
        }
        return;
    }

    // RENDER from here if needed.
}

} // namespace CodeHero

