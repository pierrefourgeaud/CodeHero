// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/platform/common/CommonSharedLibraryHandler.h"

#include <tuple>

#include "core/logger/Logger.h"

namespace CodeHero {

// static
CommonSharedLibraryHandler::ShLibHandle CommonSharedLibraryHandler::GetLibraryHandle(
    const String& iName) {
    std::ignore = iName;
    LOGF << "SharedLibraryHandler::GetLibraryHande not available on this platform.";
    return nullptr;
}

// static
CommonSharedLibraryHandler::ShLibExport CommonSharedLibraryHandler::GetLibraryExport(
    CommonSharedLibraryHandler::ShLibHandle iHandle,
    const StringANSI& iExport) {
    std::ignore = iHandle;
    std::ignore = iExport;
    LOGF << "SharedLibraryHandler::GetLibraryExport not available on this platform.";
    return nullptr;
}

} // namespace CodeHero