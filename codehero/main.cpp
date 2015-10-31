// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "./main/main.h"

#include <iostream>
#include <cstdlib>

int main() {
    CodeHero::Main app;

    if (app.Start() != CodeHero::Error::OK) {
        std::cerr << "Error during the startup process... Quitting..." << std::endl;
        return EXIT_FAILURE;
    }

    if (app.Run() != CodeHero::Error::OK) {
        std::cerr << "Error during runtime process... Quitting..." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
