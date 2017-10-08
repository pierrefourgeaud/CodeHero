// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/fileaccess.h"
#include <logger.h>
#include <sys/stat.h>

namespace CodeHero {

FileAccess::FileAccess() {}

FileAccess::~FileAccess() {
    Close();
}

Error FileAccess::Open(const std::string& iFilename, Flags iFlags) {
    Close();

    std::string modeString;
    switch (iFlags) {
    case READ:       modeString = "rb"; break;
    case WRITE:      modeString = "wb"; break;
    case READ_WRITE: modeString = "rb+"; break;
    default: return ERR_INVALID_PARAMETER;
    };

    LOGD2 << "[FileAccess::Open]: Opening " << iFilename << " with mode " << modeString << std::endl;

    m_pFile = std::fopen(iFilename.c_str(), modeString.c_str());
    m_Name = iFilename;

    return !IsOpen() ? ERR_FILE_NOT_FOUND : OK;
}

void FileAccess::Close() {
    if (!IsOpen()) { return; }

    LOGD2 << "[FileAccess::Close]: Closing " << m_Name << "." << std::endl;

    fclose(m_pFile);
    m_pFile = nullptr;
}

int FileAccess::Read(uint8_t* oData, int iLength) {
    if (!IsOpen()) {
        m_LastError = ERR_NO_FILE_OPENED;
        return 0;
    }

    int res = std::fread(oData, sizeof(uint8_t), iLength, m_pFile);
    _CheckErrors();
    return res;
}

uint8_t FileAccess::Read8() {
    uint8_t byte = 0;

    Read(&byte, 1);
    return byte;
}

uint16_t FileAccess::Read16() {
    uint16_t res = 0;

    uint8_t a = Read8();
    uint8_t b = Read8();

    res = b;
    res <<= 8;
    res |= a;

    return res;
}

uint32_t FileAccess::Read32() {
    uint32_t res = 0;

    uint16_t a = Read16();
    uint16_t b = Read16();

    res = b;
    res <<= 16;
    res |= a;

    return res;
}

std::string FileAccess::ReadAll() {
    size_t size = GetSize();

    std::string out(size, '\0');
    Read((uint8_t*)&out[0], size);
    return std::move(out);
}

int32_t FileAccess::GetPos() {
    if (!IsOpen()) {
        return 0;
    }

    int32_t pos = std::ftell(m_pFile);
    return pos;
}

bool FileAccess::IsEOF() const {
    return IsOpen() && feof(m_pFile);
}

Error FileAccess::SeekTop() {
    if (!IsOpen()) { return ERR_NO_FILE_OPENED; }

    std::rewind(m_pFile);
    return OK;
}

Error FileAccess::Seek(int64_t iPosition) {
    if (!IsOpen()) { return ERR_NO_FILE_OPENED; }

    if (std::fseek(m_pFile, iPosition, SEEK_SET) != 0) {
        return FAILED;
    }

    return OK;
}

Error FileAccess::SeekEnd() {
    if (!IsOpen()) { return ERR_NO_FILE_OPENED; }

    if (std::fseek(m_pFile, 0, SEEK_END) != 0) {
        return FAILED;
    }

    return OK;
}

size_t FileAccess::GetSize() {
    if (m_Size == (std::numeric_limits<std::size_t>::max)()) {
        // Although fseek/ftell would allow us to reuse the exising file handle here,
        // it is generally unsafe because:
        //  - For binary streams, it is not technically well-defined
        //  - For text files the results are meaningless
        // That's why we use the safer variant fstat here.
        //
        // See here for details:
        // https://www.securecoding.cert.org/confluence/display/c/FIO19-C.+Do+not+use+fseek%28%29+and+ftell%28%29+to+compute+the+size+of+a+regular+file
#if defined _WIN32 && !defined __GNUC__
        struct __stat64 fileStat;
        int err = _stat64(m_Name.c_str(), &fileStat);
        if (err != 0) {
            return 0;
        }
        m_Size = static_cast<size_t>(fileStat.st_size);
#else
        struct stat fileStat;
        int err = stat(m_Name.c_str(), &fileStat);
        if (err != 0) {
            return 0;
        }
        m_Size = static_cast<size_t>(fileStat.st_size);
#endif
    }

    return m_Size;
}

bool FileAccess::IsOpen() const {
    return m_pFile != nullptr;
}

bool FileAccess::Exists(const std::string& iFilename) {
    // TODO use new C++ features
    FILE* fp;
    fp = fopen(iFilename.c_str(), "rb");

    if (fp == nullptr) { return false; }

    fclose(fp);
    return true;
}

void FileAccess::_CheckErrors() {
    if (!IsOpen()) { return; }

    if (feof(m_pFile)) {
        m_LastError = ERR_FILE_EOF;
    }
}

}  // namespace CodeHero
