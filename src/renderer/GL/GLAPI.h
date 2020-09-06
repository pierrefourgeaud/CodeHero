// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/HAL/Platform.h"

#if !defined(RENDERER_GL_API)
#if defined(RENDERER_GL_API_EXPORT)
#define RENDERER_GL_API SHLIBEXPORT
#else
#define RENDERER_GL_API SHLIBIMPORT
#endif
#endif