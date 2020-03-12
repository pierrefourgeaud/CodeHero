// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/HAL/Platform.h"

#if !defined(CORE_API)
#if defined(CORE_API_EXPORT)
#define CORE_API SHLIBEXPORT
#else
#define CORE_API SHLIBIMPORT
#endif
#endif