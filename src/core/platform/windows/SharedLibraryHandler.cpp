// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/platform/windows/SharedLibraryHandler.h"

#include <Windows.h>

#include "core/Macros.h"
#include "core/logger/Logger.h"

namespace CodeHero {

const String g_DLLEXTENSION = TEXT(".dll");

CommonSharedLibraryHandler::ShLibHandle SharedLibraryHandler::GetLibraryHandle(
    const String& iName) {
    const String fullFilename = iName + g_DLLEXTENSION;
    HINSTANCE hinstLib = LoadLibrary(fullFilename.c_str());

    if (hinstLib) {
        LOGD2 << "GetLibraryHandle loaded " << fullFilename;
        return hinstLib;
    } else {
        LOGE << "Failed to load " << fullFilename << ", GetLastError=" << GetLastError();
        return nullptr;
    }
}

CommonSharedLibraryHandler::ShLibExport SharedLibraryHandler::GetLibraryExport(
    CommonSharedLibraryHandler::ShLibHandle iHandle,
    const StringANSI& iExport) {
    CommonSharedLibraryHandler::ShLibExport func =
        GetProcAddress(static_cast<HMODULE>(iHandle), iExport.c_str());
    if (func) {
        LOGD2 << "GetLibraryExport loaded " << CastANSIToString(iExport);
        return func;
    } else {
        LOGD2 << "Failed to load '" << CastANSIToString(iExport)
              << "', GetLastError=" << GetLastError();
        return nullptr;
    }
}

} // namespace CodeHero