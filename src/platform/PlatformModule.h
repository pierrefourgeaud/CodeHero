// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/IModule.h"

namespace CodeHero {

// Forward declaration
class IPlatformWindow;
struct PlatformWindowParams;

class PlatformModule : public IModule {
 public:
    // NOTE: Factory method in CodeHero are written with Create* style. This is
    // the only exception throughout the code because Windows headers define
    // a CreateWindow macro that conflict with this. There are methods to cope
    // with this but I don't have the time nor the will to deal with that so
    // MakeWindow it is.
    virtual IPlatformWindow* MakeWindow(const PlatformWindowParams& iParams);
};

} // namespace CodeHero