// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_MAIN_MAIN_H_
#define CODEHERO_MAIN_MAIN_H_

#include <memory>
#include "core/errors.h"
#include "core/typedefs.h"

// Forward declaration
class ILogListener;

namespace CodeHero {

// Forward declaration
class EngineContext;

class Main {
public:
    Main();
    ~Main();

    Error Start();
    Error Run();

private:
    void _Initialize();
    void _Cleanup();

    void _LoadDrivers();
    void _UnloadDrivers();

    std::unique_ptr<ILogListener> m_pFileLogger;
    std::unique_ptr<ILogListener> m_pConsoleLogger;

    std::shared_ptr<EngineContext> m_pContext;
};

} // namespace CodeHero

#endif // CODEHERO_MAIN_MAIN_H_
