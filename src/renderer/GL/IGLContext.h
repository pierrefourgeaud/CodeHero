// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <memory>

namespace CodeHero {

// Forward declarations
class IPlatformWindow;

class IGLContext {
 public:
    virtual ~IGLContext() {}

    virtual bool Create() = 0; // TODO(pierre) Decide if create is better than initialize
    virtual void MakeCurrent(const std::unique_ptr<IPlatformWindow>& iWindow) = 0;
};

} // namespace CodeHero