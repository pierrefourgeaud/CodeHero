// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_INPUT_INPUT_H_
#define CODEHERO_INPUT_INPUT_H_

#include <memory>
#include <unordered_set>
#include "input/inputevents.h"
#include "core/system.h"

namespace CodeHero {

// Forward declaration
class EngineContext;

class Input : public System {
public:
    OBJECT(Input)

    Input(const std::shared_ptr<EngineContext>& iContext);
    ~Input();

    Error Initialize() { return OK; }
    Error Cleanup() { return OK; }

    void Update();

    void HandleKey(Key iKey, KeyEvent iAction);

    // Keyboard
    bool IsKeyPressed(Key iKey) const;

private:
    std::unordered_set<Key> m_KeyPressed;
};

} // namespace CodeHero

#endif // CODEHERO_INPUT_INPUT_H_