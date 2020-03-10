// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "codehero/CodeHero.h"

#include "core/ModuleManager.h"

#include <cstdlib>
#include <iostream>

#include "core/logger/Logger.h"
#include "core/logger/WConsoleLogger.h"

#include "renderer/GL/RendererGLModule.h"
#include "renderer/Renderer.h"

int main() {
    CodeHero::SimpleLogger::ReportingLevel() = CodeHero::ELogLevel::Debug1;
    std::unique_ptr<CodeHero::WConsoleLogger> cl(new CodeHero::WConsoleLogger());
    CodeHero::SimpleLogger::AddListener(cl.get());

    CodeHero::CodeHero app;

    auto mgr = std::make_unique<CodeHero::ModuleManager>();
    auto rendererModule =
        mgr->LoadModuleType<CodeHero::RendererGLModule>(TEXT("CodeHero.Renderer.OpenGL"));
    auto r = rendererModule->CreateRenderer();
    r->Draw();

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
