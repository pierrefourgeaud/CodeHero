// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/IModule.h"

namespace CodeHero {

class DummyModule : public IModule {
 public:
    virtual void Dummy();
};

} // namespace CodeHero