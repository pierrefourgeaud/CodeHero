// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_RENDERWINDOW_H_
#define CODEHERO_CORE_RENDERWINDOW_H_

#include "./core/errors.h"

namespace CodeHero {

class RenderWindow {
public:
    virtual ~RenderWindow() {}

    virtual Error Create(int iWidth, int iHeight) = 0;

    virtual bool ShouldClose() const = 0;

    virtual void SwapBuffers() = 0;

private:
};

} // namespace CodeHero

#endif // CODEHERO_CORE_RENDERWINDOW_H_
