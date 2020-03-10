// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include "core/platform/common/CommonSharedLibraryHandler.h"

namespace CodeHero {

class SharedLibraryHandler : public CommonSharedLibraryHandler {
 public:
    static CommonSharedLibraryHandler::ShLibHandle GetLibraryHandle(const String& iName);
    static CommonSharedLibraryHandler::ShLibExport GetLibraryExport(
        CommonSharedLibraryHandler::ShLibHandle iHandle,
        const StringANSI& iName);
};

} // namespace CodeHero