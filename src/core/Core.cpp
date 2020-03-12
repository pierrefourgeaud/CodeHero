// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/Core.h"

#include <memory>

#include "core/logger/ILogListener.h"
#include "core/logger/Logger.h"
#include "core/logger/WConsoleLogger.h"

namespace CodeHero {

std::unique_ptr<WConsoleLogger>& ConsoleLoggerInstance() {
    static auto cl = std::make_unique<WConsoleLogger>();
    return cl;
}

void CoreInitialize() {
    CodeHero::SimpleLogger::ReportingLevel() = CodeHero::ELogLevel::Debug1;
    CodeHero::SimpleLogger::AddListener(ConsoleLoggerInstance().get());
}

void CoreTearDown() {
    ConsoleLoggerInstance().reset();
}

} // namespace CodeHero