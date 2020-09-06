// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/String.h"
#include "core/TypeDefs.h"

namespace CodeHero {

enum WindowFlags {
    WF_RESET = 0,
    // Default dimension set by the platform function. If the platform
    // doesn't provide default dimensions, CodeHero will provide a reasonable
    // default.
    // *If set, the Window creation function will ignore the width and height parameters.*
    WF_DIM_DEFAULT = 1 << 0,
    // Default position set by the platform function. If the platform
    // doesn't provide default positions, CodeHero will provide a reasonable
    // default.
    // *If set, the Window creation function will ignore the x and y parameters.*
    WF_POS_DEFAULT = 1 << 2,
};

struct PlatformWindowParams {
    uint32_t flags = WindowFlags::WF_RESET;

    String title = String(TEXT("CodeHero"));

#ifdef PLATFORM_WINDOWS
    String windowClassName = String(TEXT("CodeHeroWindow"));
#endif

    // Dimensions + positions
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t x = 0;
    uint32_t y = 0;

    // TODO(pierre): Icon
};

} // namespace CodeHero