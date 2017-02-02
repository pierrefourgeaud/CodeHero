// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/filesystem.h"

namespace CodeHero {

void FileSystem::SplitPath(const std::string& iFullPath,
                           std::string& oPath,
                           std::string& oFileName,
                           std::string& oExtension) {
    std::string pathCopy = iFullPath;

    auto extSeparator = pathCopy.rfind('.');
    auto lastSeparator = pathCopy.rfind(FileSystem::PathSeperator);

    if (extSeparator != std::string::npos &&
        (lastSeparator == std::string::npos || extSeparator > lastSeparator)) {
        oExtension = pathCopy.substr(extSeparator + 1);
        pathCopy = pathCopy.substr(0, extSeparator);
    }

    lastSeparator = pathCopy.rfind(FileSystem::PathSeperator);
    if (lastSeparator != std::string::npos) {
        oFileName = pathCopy.substr(lastSeparator + 1);
        oPath = pathCopy.substr(0, lastSeparator);
    } else {
        oFileName = pathCopy;
    }
}

std::string FileSystem::GetExtension(const std::string& iPath) {
    std::string path, fileName, extension;
    FileSystem::SplitPath(iPath, path, fileName, extension);
    return extension;
}

} // namespace CodeHero
