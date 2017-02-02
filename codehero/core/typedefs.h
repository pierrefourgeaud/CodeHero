// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPEDEFS_H_
#define CODEHERO_CORE_TYPEDEFS_H_

namespace CodeHero {

#include <cstdint>
#include <memory>

template<typename T>
std::shared_ptr<T> MakeSharedArray(uint64_t size)
{
    return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

template<typename T>
std::unique_ptr<T> MakeUniqueArray(uint64_t size)
{
    return std::unique_ptr<T>(new T[size], std::default_delete<T[]>());
}

#if defined(_WIN32) || defined(_WIN64) || \
    defined(__WIN32__) || defined(__TOS_WIN__) || \
    defined(__WINDOWS__)
#   undef CH_OS_WINDOWS
#   define CH_OS_WINDOWS 1
#endif

}  // namespace CodeHero

#endif  // CODEHERO_CORE_TYPEDEFS_H_
