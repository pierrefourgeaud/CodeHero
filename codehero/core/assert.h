// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_ASSERT_H_
#define CODEHERO_CORE_ASSERT_H_

#include <logger.h>
#include <cassert>

#define CH_ASSERT(cond)                                     \
    if (!(cond)) {                                          \
        LOGE << "Assertion failed: " << #cond << std::endl; \
    }                                                       \
    assert(cond);

#endif // CODEHERO_CORE_ASSERT_H_
