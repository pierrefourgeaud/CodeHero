// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/rendersystem.h"
#include <logger.h>
#include "graphics/batch.h"
#include "graphics/scene.h"
#include "graphics/viewport.h"

#include "graphics/material.h"
#include "graphics/mesh.h"
#include "graphics/technique.h"

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
            auto batches = viewport->GetScene()->GetBatches(viewport->GetCamera());

            size_t nbBatches = batches.size();
            // Before rendering it, let's sort it
            // TODO(pierre) We should probably optimize that.
            // Some ideas, research:
            // - Mutithreaded sort? With merge at the end?
            // - I heard about order-independent-transparency, doesn't that mean we don't need
            //   to sort the objects anymore?
            // - Can we cache the sorthing also?
            std::sort(batches.begin(), batches.end(), [](const Batch& left, const Batch& right) {
                if (left.GetMesh()->GetMaterial()->GetTechnique()->IsBlendEnabled() &&
                    !right.GetMesh()->GetMaterial()->GetTechnique()->IsBlendEnabled()) {
                    return false;
                }

                if (!left.GetMesh()->GetMaterial()->GetTechnique()->IsBlendEnabled() &&
                    right.GetMesh()->GetMaterial()->GetTechnique()->IsBlendEnabled()) {
                    return true;
                }

                // If we are comparing to non alpha object, then it is front to back else
                // back  to front.
                if (!left.GetMesh()->GetMaterial()->GetTechnique()->IsBlendEnabled()) {
                    return left.GetDistanceFromCamera() < right.GetDistanceFromCamera();
                }

                return left.GetDistanceFromCamera() > right.GetDistanceFromCamera();
            });

            for (size_t j = 0; j < nbBatches; ++j) {
                batches[j].Draw(*this, viewport->GetCamera());
            }
        }
    }

    // RENDER from here if needed.
}

} // namespace CodeHero
