// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "dummy/DummyModule.h"

#include "core/logger/Logger.h"

namespace CodeHero {

IMPLEMENT_MODULE(DummyModule)

void DummyModule::Dummy() {
    LOGI << "DUMMY";
}

} // namespace CodeHero