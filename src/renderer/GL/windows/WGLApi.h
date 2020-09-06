// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

// -----------------------------------------------------------
// This file was generated following the 4.6 headers taken
// from the OpenGL Khronos registry on the 3/22/2020.
//
// NOTE: Extensions are not taken into account yet. This is
// something to add when we start using some.
// -----------------------------------------------------------

#pragma once

#include <wingdi.h>

// This should be after the windows includes
#include <GL/glcorearb.h>
#include <GL/wgl.h>

#define FOREACH_WGL_ENTRYPOINTS(Macro)                                  \
    Macro(PFNWGLCOPYCONTEXTPROC, wglCopyContext);                       \
    Macro(PFNWGLCREATECONTEXTPROC, wglCreateContext);                   \
    Macro(PFNWGLCREATELAYERCONTEXTPROC, wglCreateLayerContext);         \
    Macro(PFNWGLDELETECONTEXTPROC, wglDeleteContext);                   \
    Macro(PFNWGLDESCRIBELAYERPLANEPROC, wglDescribeLayerPlane);         \
    Macro(PFNWGLGETCURRENTCONTEXTPROC, wglGetCurrentContext);           \
    Macro(PFNWGLGETCURRENTDCPROC, wglGetCurrentDC);                     \
    Macro(PFNWGLGETLAYERPALETTEENTRIESPROC, wglGetLayerPaletteEntries); \
    Macro(PFNWGLGETPROCADDRESSPROC, wglGetProcAddress);                 \
    Macro(PFNWGLMAKECURRENTPROC, wglMakeCurrent);                       \
    Macro(PFNWGLREALIZELAYERPALETTEPROC, wglRealizeLayerPalette);       \
    Macro(PFNWGLSETLAYERPALETTEENTRIESPROC, wglSetLayerPaletteEntries); \
    Macro(PFNWGLSHARELISTSPROC, wglShareLists);                         \
    Macro(PFNWGLSWAPLAYERBUFFERSPROC, wglSwapLayerBuffers);             \
    Macro(PFNWGLUSEFONTBITMAPSPROC, wglUseFontBitmaps);                 \
    Macro(PFNWGLUSEFONTBITMAPSAPROC, wglUseFontBitmapsA);               \
    Macro(PFNWGLUSEFONTBITMAPSWPROC, wglUseFontBitmapsW);               \
    Macro(PFNWGLUSEFONTOUTLINESPROC, wglUseFontOutlines);               \
    Macro(PFNWGLUSEFONTOUTLINESAPROC, wglUseFontOutlinesA);             \
    Macro(PFNWGLUSEFONTOUTLINESWPROC, wglUseFontOutlinesW);

#define DECLARE_WGL_FUNCTIONS(Type, FuncName) static Type FuncName##Fn = nullptr;
FOREACH_WGL_ENTRYPOINTS(DECLARE_WGL_FUNCTIONS)
#undef DECLARE_WGL_FUNCTIONS

// I was thinking to handle the extension separatly and maybe not just stop
// if this extension is not available. For now, it will be as it is but I will
// keep that in mind. This is why it was added separately.
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;