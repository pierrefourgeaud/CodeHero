// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#ifdef PLATFORM_WINDOWS
#include "renderer/GL/windows/GLContextWGL.h"
#else
#error GLContext is not implemented on this platform.
#endif