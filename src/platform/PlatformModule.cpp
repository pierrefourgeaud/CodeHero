// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "platform/PlatformModule.h"

#include "core/logger/Logger.h"
#include "platform/HAL/PlatformWindow.h"

namespace CodeHero {

IMPLEMENT_MODULE(PlatformModule)

IPlatformWindow* PlatformModule::MakeWindow(const PlatformWindowParams& iParams) {
    PlatformWindow* window = new PlatformWindow();

    window->Initialize(iParams);
    return window;
}

} // namespace CodeHero