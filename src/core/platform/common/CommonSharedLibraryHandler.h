// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/String.h"

namespace CodeHero {

class CommonSharedLibraryHandler {
 public:
    using ShLibHandle = void*;
    using ShLibExport = void*;

    static ShLibHandle GetLibraryHandle(const String& iName);
    // TODO(pierre) Pass a String and make a conversion from String to ANSI
    static ShLibExport GetLibraryExport(ShLibHandle iHandle, const StringANSI& iExport);
};

} // namespace CodeHero