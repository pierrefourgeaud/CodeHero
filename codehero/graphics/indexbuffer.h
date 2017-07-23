// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_INDEXBUFFER_H_
#define CODEHERO_GRAPHICS_INDEXBUFFER_H_

#include "core/gpuobject.h"
#include "core/typedefs.h"

namespace CodeHero {

class IndexBuffer : public GPUObject {
public:
    explicit IndexBuffer(bool iIsDynamic = false) : m_IsDynamic(iIsDynamic) {}
    virtual ~IndexBuffer() {}

    virtual void Use() {}
    virtual void Unuse() {}

    virtual void SetData(const void* iData, uint32_t iIndexSize, bool iIsDynamic = false);

    uint32_t GetSize() const { return m_IndexSize; }

protected:
    uint32_t m_IndexSize = 0;
    bool m_IsDynamic = false;

    virtual void _SetDataImpl(const void* iData) = 0;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_INDEXBUFFER_H_
