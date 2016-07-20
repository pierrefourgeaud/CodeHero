// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_FILEACCESS_H_
#define CODEHERO_CORE_FILEACCESS_H_

#include <cstdio>
#include <string>

#include "./errors.h"

namespace CodeHero {

class FileAccess {
public:
    enum Flags {
        READ,
        WRITE,
        READ_WRITE
    };

    FileAccess();
    virtual ~FileAccess();

    Error Open(const std::string& iFilename, Flags iFlags);
    void Close();

    int Read(uint8_t* oData, int iLength);
    uint8_t Read8();

    bool IsEOF() const;

    Error SeekTop();
    Error Seek(int32_t iPosition);
    Error SeekEnd();

    bool IsOpen() const;

    // Statics
    static bool Exists(const std::string& iFilename);

private:
    FILE* m_pFile = nullptr;
    std::string m_Name;
    Error m_LastError = OK;

    void _CheckErrors();
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_FILEACCESS_H_
