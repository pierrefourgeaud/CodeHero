// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_UTILS_H_
#define CODEHERO_CORE_UTILS_H_

#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace CodeHero {

// TODO(pierre) move to string utils
// StartsWith
// EndsWith
// Split
// Trim
// Join
inline bool StartsWith(const std::string& iStr, const std::string& iPrefix) {
    if (iPrefix.size() > iStr.size()) { return false; }
    return std::equal(iPrefix.begin(), iPrefix.end(), iStr.begin());
}

inline bool EndsWith(const std::string& iStr, const std::string& iSuffix) {
    if (iSuffix.size() > iStr.size()) { return false; }
    return std::equal(iSuffix.rbegin(), iSuffix.rend(), iStr.rbegin());
}

template<class Out>
void Split(const std::string& iS, char iDelim, Out oResult) {
    std::stringstream ss;
    ss.str(iS);
    std::string item;
    while (std::getline(ss, item, iDelim)) {
        *(oResult++) = item;
    }
}

std::vector<std::string> Split(const std::string& iS, char iDelim);

// trim from start (in place)
inline void LTrim(std::string& ioS) {
    ioS.erase(ioS.begin(), std::find_if(ioS.begin(), ioS.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void RTrim(std::string& ioS) {
    ioS.erase(std::find_if(ioS.rbegin(), ioS.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), ioS.end());
}

// trim from both ends (in place)
inline void Trim(std::string& ioS) {
    LTrim(ioS);
    RTrim(ioS);
}

std::string Join(std::vector<std::string>& iA, char iDelim);

template <class T>
bool IsIn(const T& iToFind, const std::vector<T>& iArray) {
    return std::find(iArray.begin(), iArray.end(), iToFind) != std::end(iArray);
}

}  // namespace CodeHero

#endif  // CODEHERO_CORE_UTILS_H_
