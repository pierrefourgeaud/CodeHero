// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "platform/IPlatformWindow.h"

// If this file start to be included to much, we can start to use a PIMPL
// implementation here.
#include <windows.h>

namespace CodeHero {

class WindowsPlatformWindow : public IPlatformWindow {
 public:
    WindowsPlatformWindow();
    ~WindowsPlatformWindow() override;

    bool Initialize(const PlatformWindowParams& iParams) override;
    bool Destroy() override;

    virtual void* GetHandle() const override { return (void*)m_pHWnd; }
    virtual void* GetDeviceContext() const override { return (void*)m_pDeviceContext; }

 private:
    static LRESULT CALLBACK WndProc(HWND iHWnd, UINT iMsg, WPARAM iWParam, LPARAM iLParam);
    LRESULT _HandleMessage(HWND iHWnd, UINT iMsg, WPARAM iWParam, LPARAM iLParam);

    bool _RegisterClass(const PlatformWindowParams& iParams);

    HWND m_pHWnd;
    HDC m_pDeviceContext;
};

using PlatformWindow = WindowsPlatformWindow;

} // namespace CodeHero