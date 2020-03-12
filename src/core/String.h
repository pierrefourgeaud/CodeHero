// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <codecvt>
#include <locale>
#include <string>

namespace CodeHero {

using String = std::wstring;
using StringANSI = std::string; // Some system function need that.

inline String CastANSIToString(const std::string& iString) {
    return std::wstring_convert<std::codecvt_utf8<String::value_type>>().from_bytes(iString);
}

inline String CastANSIToString(const char* iString) {
    return std::wstring_convert<std::codecvt_utf8<String::value_type>>().from_bytes(iString);
}

} // namespace CodeHero