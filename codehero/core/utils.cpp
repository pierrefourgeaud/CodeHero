// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <core/utils.h>
#include <locale>

namespace CodeHero {

std::vector<std::string> Split(const std::string& iS, char iDelim) {
    std::vector<std::string> elems;
    Split(iS, iDelim, std::back_inserter(elems));
    return elems;
}

void ToLowerCase(std::string& oS) {
    // We should not use directly tolower here
    // cf. http://en.cppreference.com/w/cpp/string/byte/tolower
    // Basically, using directly std::tolower is undefined in that case
    std::transform(oS.begin(), oS.end(), oS.begin(), [](unsigned char c) { return std::tolower(c); });
}

std::string LowerCased(const std::string& iS) {
    std::string s(iS.size(), '\0');
    // We should not use directly tolower here
    // cf. http://en.cppreference.com/w/cpp/string/byte/tolower
    // Basically, using directly std::tolower is undefined in that case
    std::transform(iS.begin(), iS.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return std::move(s);
}

std::string Join(std::vector<std::string>& iA, char iDelim /* = ' '*/) {
    std::string res;
    size_t size = iA.size();
    for (size_t i = 0; i < size; ++i) {
        if (!res.empty()) {
            res += iDelim;
        }

        res += iA[i];
    }
    return res;
}

} // namespace CodeHero