// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_FILEACCESS_H_
#define CODEHERO_CORE_FILEACCESS_H_

#include <cstdio>
#include <limits>
#include <string>

#include "core/errors.h"

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
    uint16_t Read16();
    uint32_t Read32();
    std::string ReadAll();

    bool IsEOF() const;

    Error SeekTop();
    Error Seek(int64_t iPosition);
    Error SeekEnd();

    int32_t GetPos();

    bool IsOpen() const;

    size_t GetSize();

    // TODO(pierre) We should split the name of the file and the rest (directory)
    std::string GetName() const { return m_Name; }

    // Statics
    static bool Exists(const std::string& iFilename);

private:
    FILE* m_pFile = nullptr;
    std::string m_Name;
    Error m_LastError = OK;

    size_t m_Size = (std::numeric_limits<std::size_t>::max)();

    void _CheckErrors();
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_FILEACCESS_H_
