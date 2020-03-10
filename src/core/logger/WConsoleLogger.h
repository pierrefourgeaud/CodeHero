// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <iostream>

#include "core/TypeDefs.h"
#include "core/logger/ILogListener.h"
#include "core/logger/Logger.h"

namespace CodeHero {

class WConsoleLogger : public ILogListener {
 public:
    WConsoleLogger() = default;
    ~WConsoleLogger() override {}

    virtual void Notify(const String& iMsg, ELogLevel iLevel) {
        if (iLevel <= ELogLevel::Error) {
            std::wcerr << iMsg << std::endl;
        } else {
            std::wcout << iMsg << std::endl;
        }
    }
};

} // namespace CodeHero