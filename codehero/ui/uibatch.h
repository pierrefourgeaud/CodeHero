// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_UIBATCH_H_
#define CODEHERO_UI_UIBATCH_H_

#include <memory>

namespace CodeHero {

class Texture;
class VertexBuffer;
class IndexBuffer;

class UIBatch {
public:
    void SetTexture(std::shared_ptr<Texture> iTexture);
    void SetVertexBuffer(std::shared_ptr<VertexBuffer> iVertexBuffer,
                         uint32_t iStart = 0,
                         uint32_t iCount = 0);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& iIndexBuffer);

    std::shared_ptr<Texture> GetTexture() const { return m_pTexture; }
    std::shared_ptr<VertexBuffer> GetVertexBuffer() const { return m_pVertexBuffer; }
    std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return m_pIndexBuffer; }
    uint32_t GetStart() const { return m_Start; }
    uint32_t GetCount() const { return m_Count; }

private:
    std::shared_ptr<Texture> m_pTexture;
    std::shared_ptr<VertexBuffer> m_pVertexBuffer;
    std::shared_ptr<IndexBuffer> m_pIndexBuffer;
    uint32_t m_Start = 0;
    uint32_t m_Count = 0;
};

} // namespace CodeHero

#endif // CODEHERO_UI_UIBATCH_H_
