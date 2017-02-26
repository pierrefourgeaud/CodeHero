// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_MAIN_MAIN_H_
#define CODEHERO_MAIN_MAIN_H_

#include <memory>
#include "core/typedefs.h"
#include "core/errors.h"

// Forward declaration
class ILogListener;

namespace CodeHero {

// Forward declaration
class EngineContext;
class RenderWindow;
//template <class T> class ResourceLoader;
//class Image;

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

    std::unique_ptr<RenderWindow> m_pMainWindow;

    //std::shared_ptr<ResourceLoader<Image>> m_pImageLoader;
};

}  // namespace CodeHero

#endif  // CODEHERO_MAIN_MAIN_H_
