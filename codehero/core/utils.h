// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_UTILS_H_
#define CODEHERO_CORE_UTILS_H_

#include <algorithm>
#include <string>
#include <type_traits>
#include <vector>

namespace CodeHero {

// TODO(pierre) move to string utils
static bool EndsWith(const std::string& iStr, const std::string& iSuffix) {
    if (iSuffix.size() > iStr.size()) { return false; }
    return std::equal(iSuffix.rbegin(), iSuffix.rend(), iStr.rbegin());
}

template <class T>
static bool IsIn(const T& iToFind, const std::vector<T>& iArray) {
    return std::find(iArray.begin(), iArray.end(), iToFind) != std::end(iArray);
}

}  // namespace CodeHero

#endif  // CODEHERO_CORE_UTILS_H_
