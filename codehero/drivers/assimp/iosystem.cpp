// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "drivers/assimp/iosystem.h"
#include "core/assert.h"
#include "core/fileaccess.h"

namespace CodeHero {

/*
 * IOStream
 */
IOStream::IOStream(FileAccess* iFileAccess, bool iTransferOwnership)
    : m_pFileAccess(iFileAccess), m_HasOwnership(iTransferOwnership) {}

IOStream::~IOStream() {
    if (m_HasOwnership) {
        delete m_pFileAccess;
    }
}

size_t IOStream::Read(void* oBuffer, size_t iSize, size_t iCount) {
    CH_ASSERT(m_pFileAccess);
    CH_ASSERT(oBuffer != nullptr && iSize != 0 && iCount != 0);

    return m_pFileAccess->Read(static_cast<uint8_t*>(oBuffer), iSize * iCount) / iSize;
}

size_t IOStream::Write(const void* iBuffer, size_t iSize, size_t iCount) {
    (void)iBuffer;
    (void)iSize;
    (void)iCount;
#ifdef _MSC_VER
    __pragma(warning(push)) __pragma(warning(disable : 4127))
#endif
        CH_ASSERT(false && "Should be implemented.");
#ifdef _MSC_VER
    __pragma(warning(pop))
#endif
        return 0;
}

aiReturn IOStream::Seek(size_t iOffset, aiOrigin iOrigin) {
    (void)iOffset;
    (void)iOrigin;

    CH_ASSERT(m_pFileAccess);

    // TODO(pierre) Let file access apply the second argument
    // for the seek too.

    // TODO(pierre) Assimp verify the value for aiOrigin,
    // should we do the same ?

    return m_pFileAccess->Seek(iOffset) == Error::OK ? aiReturn_SUCCESS : aiReturn_FAILURE;
}

size_t IOStream::Tell() const {
    CH_ASSERT(m_pFileAccess);

    return m_pFileAccess->GetPos();
}

size_t IOStream::FileSize() const {
    CH_ASSERT(m_pFileAccess);

    return m_pFileAccess->GetSize();
}

void IOStream::Flush() {
#ifdef _MSC_VER
    __pragma(warning(push)) __pragma(warning(disable : 4127))
#endif
        CH_ASSERT(false && "Should be implemented.");
#ifdef _MSC_VER
    __pragma(warning(pop))
#endif
}

/*
 * IOSystem
 */
IOSystem::IOSystem() {}

IOSystem::IOSystem(FileAccess* iFile) : m_pFileAccess(iFile) {}

IOSystem::~IOSystem() {}

bool IOSystem::Exists(const char* iFile) const {
    CH_ASSERT(iFile != nullptr);
    return FileAccess::Exists(iFile);
}

IOStream* IOSystem::Open(const char* iFile, const char* iMode /* = "rb"*/) {
    CH_ASSERT(iFile != nullptr && iMode != nullptr);

    // TODO(pierre) Do for the other modes ?

    FileAccess* file = nullptr;
    bool transferOwnership = false;
    if (!m_pFileAccess || m_pFileAccess->GetName() != iFile) {
        file = new FileAccess();
        transferOwnership = true;
        if (file->Open(iFile, FileAccess::READ) == ERR_FILE_NOT_FOUND) {
            LOGE << "[IOSystem]: File not found '" << iFile << "'." << std::endl;
            return nullptr;
        }
    } else if (m_pFileAccess) {
        file = m_pFileAccess;
    }

    return file == nullptr ? nullptr : new IOStream(file, transferOwnership);
}

void IOSystem::Close(Assimp::IOStream* iFile) {
    CH_ASSERT(iFile != nullptr);
    delete iFile;
}

} // namespace CodeHero