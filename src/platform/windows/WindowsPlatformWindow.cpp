// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "platform/Windows/WindowsPlatformWindow.h"

#include <windows.h>

#include "core/String.h"
#include "core/logger/Logger.h"
#include "platform/PlatformWindowParams.h"

namespace CodeHero {

WindowsPlatformWindow::WindowsPlatformWindow() = default;
WindowsPlatformWindow::~WindowsPlatformWindow() = default;

bool WindowsPlatformWindow::Initialize(const PlatformWindowParams& iParams) {
    _RegisterClass(iParams);

    int32_t x;
    int32_t y;
    if (iParams.flags & WindowFlags::WF_POS_DEFAULT) {
        x = CW_USEDEFAULT;
        y = CW_USEDEFAULT;
    } else {
        x = iParams.x;
        y = iParams.y;
    }

    int32_t width;
    int32_t height;
    if (iParams.flags & WindowFlags::WF_DIM_DEFAULT) {
        width = CW_USEDEFAULT;
        height = CW_USEDEFAULT;
    } else {
        width = iParams.width;
        height = iParams.height;
    }

    m_pHWnd =
        CreateWindowEx(WS_EX_APPWINDOW, iParams.windowClassName.c_str(), iParams.title.c_str(),
                       WS_BORDER | WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU, x, y, width, height,
                       nullptr, // No parent
                       nullptr, // No menu
                       GetModuleHandle(nullptr), this);

    if (!m_pHWnd) {
        MessageBox(NULL, TEXT("Window Creation Failed! Abort!"), TEXT("Error!"),
                   MB_ICONEXCLAMATION | MB_OK);

        return false;
    }

    m_pDeviceContext = GetDC(m_pHWnd);

    ShowWindow(m_pHWnd, SW_SHOW);

    return true;
}

bool WindowsPlatformWindow::Destroy() {
    if (!DestroyWindow(m_pHWnd)) {
        LOGE << "Failed to destroy window with error: " << GetLastError();
        return false;
    }

    return true;
}

// private
bool WindowsPlatformWindow::_RegisterClass(const PlatformWindowParams& iParams) {
    WNDCLASS wc = {0};

    // If the class is already registered, we exit the function early.
    // TODO(pierre) Maybe we should ensure in the code that this doesn't
    // happen ever?
    if (GetClassInfo(GetModuleHandle(nullptr), iParams.windowClassName.c_str(), &wc)) {
        return true;
    }

    wc = {0};

    // TODO(pierre) We should add this as an option when setting up a project
    HICON hIcon = nullptr;

    wc.style = CS_DBLCLKS; // Enable messages to receive double clicks.
    wc.lpfnWndProc = WindowsPlatformWindow::WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hIcon = hIcon;
    wc.hCursor = nullptr;       // We will handle the cursor ourselves
    wc.hbrBackground = nullptr; // We are handling that part
    wc.lpszMenuName = nullptr;  // No menu
    wc.lpszClassName = iParams.windowClassName.c_str();

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("Window Class Registration Failed! Abort!"), TEXT("Error!"),
                   MB_ICONEXCLAMATION | MB_OK);

        return false;
    }

    return true;
}

// static
LRESULT CALLBACK WindowsPlatformWindow::WndProc(HWND iHWnd,
                                                UINT iMsg,
                                                WPARAM iWParam,
                                                LPARAM iLParam) {
    WindowsPlatformWindow* that = nullptr;

    if (iMsg == WM_NCCREATE) {
        CREATESTRUCT* cs = (CREATESTRUCT*)iLParam;
        that = (WindowsPlatformWindow*)cs->lpCreateParams;
        SetWindowLongPtr(iHWnd, GWLP_USERDATA, (LONG_PTR)that);
    } else {
        that = (WindowsPlatformWindow*)GetWindowLongPtr(iHWnd, GWLP_USERDATA);
    }

    if (that) {
        return that->_HandleMessage(iHWnd, iMsg, iWParam, iLParam);
    } else {
        return DefWindowProc(iHWnd, iMsg, iWParam, iLParam);
    }
}

LRESULT WindowsPlatformWindow::_HandleMessage(HWND iHWnd,
                                              UINT iMsg,
                                              WPARAM iWParam,
                                              LPARAM iLParam) {
    return DefWindowProc(iHWnd, iMsg, iWParam, iLParam);
}

} // namespace CodeHero