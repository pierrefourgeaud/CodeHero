// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_FILESYSTEM_H_
#define CODEHERO_CORE_FILESYSTEM_H_

#include <string>

namespace CodeHero {

class FileSystem {
public:
#ifdef CH_OS_WINDOWS
    static const char PathSeperator = '\\';
#else
    static const char PathSeperator = '/';
#endif // CH_OS_WINDOWS

    static void SplitPath(const std::string& iFullPath,
                          std::string& oPath,
                          std::string& oFileName,
                          std::string& oExtension);

    static std::string GetExtension(const std::string& iPath);

private:
};

} // namespace CodeHero

#endif // CODEHERO_CORE_FILESYSTEM_H_
