// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_DRIVERS_ASSIMP_IOSYSTEM_H_
#define CODEHERO_DRIVERS_ASSIMP_IOSYSTEM_H_

#include <assimp/IOStream.hpp>
#include <assimp/IOSystem.hpp>

namespace CodeHero {

// Forward declaration
class FileAccess;

class IOStream : public Assimp::IOStream {
    friend class IOSystem;

   public:
    ~IOStream();
    size_t Read(void* oBuffer, size_t iSize, size_t iCount) override;
    size_t Write(const void* iBuffer, size_t iSize, size_t iCount) override;
    aiReturn Seek(size_t iOffset, aiOrigin iOrigin) override;
    size_t Tell() const override;
    size_t FileSize() const override;
    void Flush() override;

   protected:
    IOStream(FileAccess* iFile, bool iTransferOwnership);

   private:
    // There is no ownership here.
    // Limitation from the API (at the moment) makes it not possible to
    // user smart pointer here hence the raw pointer...
    // This should be fixed later.
    FileAccess* m_pFileAccess = nullptr;
    bool m_HasOwnership;
};

class IOSystem : public Assimp::IOSystem {
   public:
    IOSystem();
    explicit IOSystem(FileAccess* iFile);
    ~IOSystem();

    bool Exists(const char* iFile) const override;
    char getOsSeparator() const override { return '/'; }
    IOStream* Open(const char* iFile, const char* iMode = "rb") override;
    void Close(Assimp::IOStream* iFile) override;

   private:
    // There is no ownership here. Cannot use shared_ptr at the moment (or weak_ptr in that case)
    FileAccess* m_pFileAccess = nullptr;
};

} // namespace CodeHero

#endif // CODEHERO_DRIVERS_ASSIMP_IOSYSTEM_H_
