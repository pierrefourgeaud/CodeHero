// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "input/input.h"
#include "core/enginecontext.h"
#include "graphics/rendersystem.h"
#include "graphics/renderwindow.h"

namespace CodeHero {

Input::Input(const std::shared_ptr<EngineContext>& iContext) : System(iContext) {}

Input::~Input() {}

Error Input::Initialize() {
    RenderSystem* rs = m_pContext->GetSubsystem<RenderSystem>();

    // TODO(pierre) I don't like that we have to use the RenderSystem/Window to set some options on
    // the mouse...
    rs->GetWindow()->SetMouseVisible(
        false, true); // This should be overridable (Add a Input->SetMouseMode(...))
    return OK;
}

void Input::HandleKey(Key iKey, KeyEvent iAction) {
    switch (iAction) {
        case KeyEvent::KE_PRESS: m_KeyPressed.insert(iKey); break;
        case KeyEvent::KE_RELEASE: m_KeyPressed.erase(iKey); break;
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

void Input::HandleMouse(float iPosX, float iPosY) {
    // TODO(pierre) Could we use a setter instead ? This look hackish
    static bool firstMouse = true;
    if (firstMouse) {
        m_LastMousePosition = Vector2(iPosX, iPosY);
        firstMouse = false;
    } else {
        m_LastMousePosition = m_MousePosition;
    }
    m_MousePosition = Vector2(iPosX, iPosY);
    m_MouseMove = m_MousePosition - m_LastMousePosition;
}

void Input::Update() {
    // TODO(pierre) Should we cache this call ? This will have a small perf impact
    RenderSystem* rs = m_pContext->GetSubsystem<RenderSystem>();

    rs->PollEvents();
}

void Input::EndFrame() {
    ResetInputAcc();
}

void Input::ResetInputAcc() {
    m_MouseMove = Vector2();
}

bool Input::IsKeyPressed(Key iKey) const {
    return m_KeyPressed.find(iKey) != m_KeyPressed.end();
}

} // namespace CodeHero