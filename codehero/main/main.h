// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_MAIN_MAIN_H_
#define CODEHERO_MAIN_MAIN_H_

#include <memory>
#include "./core/typedefs.h"
#include "./core/errors.h"

// Forward declaration
class ILogListener;

namespace CodeHero {

// Forward declaration
class RenderSystem;
class RenderWindow;
class ImageLoader;

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

    std::unique_ptr<RenderSystem> m_pRS;
    std::unique_ptr<RenderWindow> m_pMainWindow;

    ImageLoader& m_ImageLoader;
};

}  // namespace CodeHero

#endif  // CODEHERO_MAIN_MAIN_H_
