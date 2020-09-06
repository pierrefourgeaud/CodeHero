// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

namespace CodeHero {

// Forward declaration
struct PlatformWindowParams;

class IPlatformWindow {
 public:
    virtual ~IPlatformWindow() {}

    virtual bool Initialize(const PlatformWindowParams& iParams) = 0;
    virtual bool Destroy() = 0;

    virtual void* GetHandle() const = 0;
    virtual void* GetDeviceContext() const = 0;
};

} // namespace CodeHero