// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/HAL/Platform.h"

#if !defined(ENGINE_API)
#if defined(ENGINE_API_EXPORT)
#define ENGINE_API SHLIBEXPORT
#else
#define ENGINE_API SHLIBIMPORT
#endif
#endif