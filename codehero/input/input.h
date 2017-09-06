// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_INPUT_INPUT_H_
#define CODEHERO_INPUT_INPUT_H_

#include <memory>
#include <unordered_set>
#include "input/inputevents.h"
#include "core/system.h"
#include "core/math/vector2.h"

namespace CodeHero {

// Forward declaration
class EngineContext;

class Input : public System {
public:
    OBJECT(Input)

    Input(const std::shared_ptr<EngineContext>& iContext);
    ~Input();

    Error Initialize();
    Error Cleanup() { return OK; }

    void Update();
    void EndFrame();

    void HandleKey(Key iKey, KeyEvent iAction);
    void HandleMouse(float iPosX, float iPosY);
    void ResetInputAcc();

    // Keyboard
    bool IsKeyPressed(Key iKey) const;

    // Mouse
    Vector2 GetMousePosition() const { return m_MousePosition; }
    Vector2 GetMouseMove() const { return m_MouseMove; }

private:
    std::unordered_set<Key> m_KeyPressed;

    Vector2 m_MousePosition;
    Vector2 m_LastMousePosition;
    // Cache the mouse move (diff between current and last position
    Vector2 m_MouseMove;
};

} // namespace CodeHero

#endif // CODEHERO_INPUT_INPUT_H_