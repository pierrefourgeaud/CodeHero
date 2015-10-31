// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_MAIN_MAIN_H_
#define CODEHERO_MAIN_MAIN_H_

#include "../core/errors.h"

// Forward declaration
class GLFWwindow;

namespace CodeHero {

// Forward declaration
class ILogListener;

class Main {
public:
    Main();
    ~Main();

    Error Start();
    Error Run();
private:
    void _Initialize();
    void _Cleanup();

    GLFWwindow* m_pWindow = nullptr;
    ILogListener* m_pFileLogger = nullptr;
};

}  // namespace CodeHero

#endif  // CODEHERO_MAIN_MAIN_H_
