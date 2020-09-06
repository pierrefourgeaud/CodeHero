// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/GLPlatform.h"

#include <windows.h>

#include "core/HAL/SharedLibraryHandler.h"
#include "core/ModuleManager.h"
#include "core/ScopeCleaner.h"
#include "core/logger/Logger.h"
#include "platform/IPlatformWindow.h"
#include "platform/PlatformModule.h"
#include "platform/PlatformWindowParams.h"
#include "renderer/GL/HAL/GLApi.h"
#include "renderer/GL/windows/GLContextWGL.h"
#include "renderer/GL/windows/WGLApi.h"

#define DEFINE_GL_FUNCTIONS(Type, FuncName) Type FuncName = nullptr;
FOREACH_GL_ENTRYPOINTS(DEFINE_GL_FUNCTIONS)
#undef DEFINE_GL_FUNCTIONS

namespace CodeHero {

// TODO(pierre) Here or in the platform module code, we could have a function to pretty print the
// result of the GetLastError()

static void* GetGLProc(SharedLibraryHandler::ShLibHandle iLibrary, const char* iFuncName) {
    void* ret = nullptr;

    ret = SharedLibraryHandler::GetLibraryExport(iLibrary, iFuncName);
    if (ret) {
        return ret;
    }

    ret = wglGetProcAddressFn(iFuncName);
    if (ret) {
        return ret;
    }

    LOGE << "GL: Failed to load " << iFuncName;
    return nullptr;
}

static bool SetPixelFormatForDeviceContext(HDC iDeviceContext) {
    PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {0};
    pixelFormatDescriptor.nSize = sizeof(pixelFormatDescriptor);
    pixelFormatDescriptor.nVersion = 1;
    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDescriptor.cColorBits = 32;
    // No depth and stencil bits, should we?
    pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

    // TODO(pierre) When we start to support stereo I guess we will have to think about the
    // PFD_STEREO flag

    auto pixelFormat = ChoosePixelFormat(iDeviceContext, &pixelFormatDescriptor);
    if (!pixelFormat || !SetPixelFormat(iDeviceContext, pixelFormat, &pixelFormatDescriptor)) {
        LOGE << "Failed to set PixelFormat. GetLastError=" << GetLastError();
        return false;
    }

    return true;
}

bool GLInit() {
    // Get the basics from openGL library
    auto library = SharedLibraryHandler::GetLibraryHandle(TEXT("opengl32"));
    if (!library) {
        LOGF << "Failed to load opengl32.dll, aborting.";
        return false;
    }

// Load the WGL bindings (wglGetProcAddress is needed later on)
#define LOAD_WGL_FUNCTIONS(Type, FuncName) \
    FuncName##Fn =                         \
        reinterpret_cast<Type>(SharedLibraryHandler::GetLibraryExport(library, #FuncName));
    FOREACH_WGL_ENTRYPOINTS(LOAD_WGL_FUNCTIONS)
#undef LOAD_WGL_FUNCTIONS

    // Some of the basic. If those functions are not loaded, we cannot move forward.
    // TODO(pierre): See over time if this check actually makes sense?
    if (!wglCreateContextFn || !wglDeleteContextFn || !wglGetProcAddressFn || !wglGetCurrentDCFn ||
        !wglGetCurrentContextFn || !wglMakeCurrentFn || !wglShareListsFn) {
        LOGF << "Failed to load wgl* methods, aborting.";
        GLTerminate();
        return false;
    }

    // Create a dummy window
    auto platform = ModuleManager::Get()->LoadModuleType<PlatformModule>(TEXT("CodeHero.Platform"));
    PlatformWindowParams params;
    params.x = 0;
    params.y = 0;
    params.width = 0;
    params.height = 0;
    params.title = TEXT("Dummy");
    params.windowClassName = TEXT("CodeHeroWindowDummy");

    auto dummyWindow = platform->MakeWindow(params);

    auto cleaner = Cleanup([&dummyWindow]() {
        GLTerminate();
        dummyWindow->Destroy();
        delete dummyWindow;
    });

    HDC dc = (HDC)dummyWindow->GetDeviceContext();
    if (!SetPixelFormatForDeviceContext(dc)) {
        return false;
    }

    // Create a temporary GL context to bind to entry points. This is needed
    // because wglGetProcAddress is specified to return nullptr for all queries if a context is not
    // current according to the MSDN documentation, and the static bindings may contain functions
    // that need to be queried wglGetProcAddress. OpenGL further warns that other error values other
    // than nullptr could also be returned from wglGetProcAddress depending on the implementations,
    // so we might need to do someting there...
    auto glContext = wglCreateContextFn(dc);
    if (!glContext) {
        LOGE << "Failed to initialize GL Context. GetLastError=" << GetLastError();
        return false;
    }

    if (!wglMakeCurrentFn(dc, glContext)) {
        LOGE << "Failed to make temporary context current. GetLastError=" << GetLastError();
        wglDeleteContextFn(glContext);
        return false;
    }

    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
        GetGLProc(library, "wglCreateContextAttribsARB"));
    if (!wglCreateContextAttribsARB) {
        LOGE << "wglCreateContextAttribsARB is not available. We consider OpenGL unsupported.";
        return false;
    }

    // We delete the temporary context to now start to use wglCreateContextAttribsARB
    wglMakeCurrentFn(nullptr, nullptr);
    wglDeleteContextFn(glContext);

    // We will attempt to create the context from the most recent to the least recent version
    // of OpenGL supported by the engine at this point.
    std::pair<int, int> supportedGLVersions[] = {{4, 6}, {4, 5}, {4, 4}, {4, 3}, {4, 2},
                                                 {4, 1}, {4, 0}, {3, 3}, {3, 2}};
    for (auto version : supportedGLVersions) {
        int attribs[] = {WGL_CONTEXT_MAJOR_VERSION_ARB,
                         version.first,
                         WGL_CONTEXT_MINOR_VERSION_ARB,
                         version.second,
                         WGL_CONTEXT_PROFILE_MASK_ARB,
                         WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                         0};

        glContext = wglCreateContextAttribsARB(dc, nullptr, attribs);
        // We successfully created a context
        if (glContext) {
            LOGI << "GL Context Version " << version.first << "." << version.second;
            break;
        }
    }

    if (!glContext) {
        LOGE << "Failed to create context. GetLastError=" << GetLastError();
        return false;
    }

    if (!wglMakeCurrentFn(dc, glContext)) {
        LOGE << "Failed to make temporary context current. GetLastError=" << GetLastError();
        wglDeleteContextFn(glContext);
        return false;
    }

#define LOAD_GL_FUNCTIONS(Type, FuncName) \
    FuncName = reinterpret_cast<Type>(GetGLProc(library, #FuncName));
    FOREACH_GL_ENTRYPOINTS(LOAD_GL_FUNCTIONS)
#undef LOAD_GL_FUNCTIONS

    wglMakeCurrentFn(nullptr, nullptr);
    wglDeleteContextFn(glContext);
    cleaner.Cancel();
    dummyWindow->Destroy();
    delete dummyWindow;

    return true;
}

void GLTerminate() {
    // TODO(pierre) Once FreeLibrary is implemented in the SharedLibraryHandler, we must implement
    // it here.
}

std::unique_ptr<IGLContext> CreateGLContext() {
    return std::unique_ptr<IGLContext>(new GLContextWGL());
}

bool SwapBuffers(const std::unique_ptr<IPlatformWindow>& iWindow) {
    return ::SwapBuffers((HDC)iWindow->GetDeviceContext());
}

} // namespace CodeHero