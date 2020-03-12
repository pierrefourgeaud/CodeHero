// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "engine/EngineLoop.h"

#include <cstdlib>
#include <iostream>

int main() {
    CodeHero::EngineLoop engineLoop;
    if (!engineLoop.PreInit()) {
        std::cerr << "Error during the startup process. Quitting." << std::endl;
        return EXIT_FAILURE;
    }

    if (!engineLoop.Init()) {
        std::cerr << "EngineLoop failed to initialize. Quitting.";
        return EXIT_FAILURE;
    }

    while (!engineLoop.ExitEngineRequested()) {
        engineLoop.Tick();
    }

    // TODO(pierre) This should probably be in a cleanup guard so whatever
    // exit path we choose, we are sure to cleanup after us.
    engineLoop.Cleanup();

    return EXIT_SUCCESS;
}
