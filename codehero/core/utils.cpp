// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <core/utils.h>

namespace CodeHero {

std::vector<std::string> Split(const std::string& iS, char iDelim) {
    std::vector<std::string> elems;
    Split(iS, iDelim, std::back_inserter(elems));
    return elems;
}

std::string Join(std::vector<std::string>& iA, char iDelim) {
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