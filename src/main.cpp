// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "./codehero/CodeHero.h"

#include <cstdlib>
#include <iostream>

int main() {
    CodeHero::CodeHero app;

    if (!app.Start()) {
        std::cerr << "Error during the startup process... Quitting..." << std::endl;
        return EXIT_FAILURE;
    }

    if (!app.Run()) {
        std::cerr << "Error during runtime process... Quitting..." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
