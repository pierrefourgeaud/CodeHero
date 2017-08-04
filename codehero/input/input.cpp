// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "input/input.h"
#include "core/enginecontext.h"
#include "graphics/rendersystem.h"

namespace CodeHero {

Input::Input(const std::shared_ptr<EngineContext>& iContext)
    : System(iContext)
{}

Input::~Input() {
}

void Input::HandleKey(Key iKey, KeyEvent iAction) {
    switch (iAction) {
    case KeyEvent::KE_PRESS:
        m_KeyPressed.insert(iKey);
        break;
    case KeyEvent::KE_RELEASE:
        m_KeyPressed.erase(iKey);
        break;
    case KeyEvent::KE_REPEAT: {
        auto key = m_KeyPressed.find(iKey);
        if (key == m_KeyPressed.end()) {
            // Here we noticed that we have a key pressed not in our set, we should add it...
            m_KeyPressed.insert(iKey);
        }
        break;
    }
    default:
        // Should never be here
        break;
    }
}

void Input::Update() {
    // TODO(pierre) Should we cache this call ? This will have a small perf impact
    RenderSystem* rs = m_pContext->GetSubsystem<RenderSystem>();

    rs->PollEvents();
}

bool Input::IsKeyPressed(Key iKey) const {
    return m_KeyPressed.find(iKey) != m_KeyPressed.end();
}

} // namespace CodeHero