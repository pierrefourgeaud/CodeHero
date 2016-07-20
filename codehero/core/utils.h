// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_UTILS_H_
#define CODEHERO_CORE_UTILS_H_

#include <type_traits>
#include <string>
#include <algorithm>

namespace CodeHero {

template <typename E>
constexpr typename std::underlying_type<E>::type to_i(E e) {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

// TODO(pierre) move to string utils
static bool EndsWith(const std::string& iStr, const std::string& iSuffix) {
    if (iSuffix.size() > iStr.size()) { return false; }
    return std::equal(iSuffix.rbegin(), iSuffix.rend(), iStr.rbegin());
}

}  // namespace CodeHero

#endif  // CODEHERO_CORE_UTILS_H_
