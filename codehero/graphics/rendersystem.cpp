// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <logger.h>
#include "graphics/batch.h"
#include "graphics/rendersystem.h"
#include "graphics/scene.h"
#include "graphics/viewport.h"

namespace CodeHero {

void RenderSystem::RegisterViewport(const std::shared_ptr<Viewport>& iViewport) {
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
            auto viewport = m_RegisteredViewports[i];
            SetViewport(viewport);
            viewport->GetScene()->PrepareVertexLights();
            auto& batches = viewport->GetScene()->GetBatches();

            size_t nbBatches = batches.size();
            for (size_t i = 0; i < nbBatches; ++i) {
                batches[i].Draw(*this, viewport->GetCamera());
            }
        }
    }

    // RENDER from here if needed.
}

} // namespace CodeHero

