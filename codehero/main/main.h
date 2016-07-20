// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_MAIN_MAIN_H_
#define CODEHERO_MAIN_MAIN_H_

#include <memory>
#include "./core/typedefs.h"
#include "./core/errors.h"

// Forward declaration
class GLFWwindow;

namespace CodeHero {

// Forward declaration
class ILogListener;

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

    static void _HandleKey(GLFWwindow* iWindow, int32_t iKey, int32_t iScancode, int32_t iAction, int32_t iMode);

    GLFWwindow* m_pWindow = nullptr;
    std::unique_ptr<ILogListener> m_pFileLogger;
    std::unique_ptr<ILogListener> m_pBufferLogger;

    ImageLoader& m_ImageLoader;
};

}  // namespace CodeHero

#endif  // CODEHERO_MAIN_MAIN_H_
