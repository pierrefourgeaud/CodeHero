// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_VERTEXBUFFER_H_
#define CODEHERO_CORE_VERTEXBUFFER_H_

#include <memory>
#include "core/typedefs.h"
#include "core/gpuobject.h"

namespace CodeHero {

class VertexBuffer : public GPUObject {
public:

    enum : uint32_t {
        EL_Position = 0,
        EL_Normal,
        EL_Color,
        EL_TexCoord,
        EL_Tangent,
        EL_Bitangent,
        EL_Max
    };

    enum : uint32_t {
        MASK_Position = 1 << 0,
        MASK_Normal = 1 << 1,
        MASK_Color = 1 << 2,
        MASK_TexCoord = 1 << 3,
        MASK_Tangent = 1 << 4,
        MASK_Bitangent = 1 << 5
    };

    VertexBuffer(bool iIsDynamic = false) : m_IsDynamic(iIsDynamic) {}
    virtual ~VertexBuffer() {}

    virtual void SetData(const void* iData, uint32_t iVertexCount, uint32_t iMasks, bool iIsDynamic = false) {
//        if (iData) {
        m_VertexCount = iVertexCount;
        m_Masks = iMasks;
        m_IsDynamic = iIsDynamic;

        _UpdateSizeImpl();
        // m_VertexSize = 1;

        m_Data = MakeSharedArray<unsigned char>(iVertexCount * m_VertexSize);
        if (iData != nullptr) {
            memcpy(m_Data.get(), iData, iVertexCount * m_VertexSize);
        }

        _SetDataImpl();
//        }
    }

    virtual void SetSubData(const void* iData, uint32_t iStart, uint32_t iCount) {
        if (iData) {
            if (m_Data.get() + iStart * m_VertexSize != iData) {
                memcpy(m_Data.get() + iStart * m_VertexSize, iData, iCount * m_VertexSize);
            }
            _SetSubDataImpl(iStart * m_VertexSize, iCount * m_VertexSize, iData);
        }
    }

    bool IsBitActive(uint32_t iBit) const { return m_Masks & iBit; }

    // Comment in the GL implementation
    virtual void Use() {};
    virtual void Unuse() {};

    uint32_t GetVertexSize() const { return m_VertexSize; }
    uint32_t GetVertexCount() const { return m_VertexCount; }
    uint32_t GetElementOffset(uint32_t iElem) const { return m_ElementOffset[iElem]; }

    virtual uint32_t GetComponentsNumber() const = 0;

protected:
    uint32_t m_VertexCount = 0;
    uint32_t m_VertexSize = 0;
    uint32_t m_Masks = 0;
    uint32_t m_ElementOffset[VertexBuffer::EL_Max] = {0};
    bool m_IsDynamic = false;
    std::shared_ptr<unsigned char> m_Data;

    virtual void _UpdateSizeImpl() = 0;
    virtual void _SetDataImpl() = 0;
    virtual void _SetSubDataImpl(uint32_t iStart, uint32_t iSize, const void* iData) = 0;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_VERTEXBUFFER_H_
