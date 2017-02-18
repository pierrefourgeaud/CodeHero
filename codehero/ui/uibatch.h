// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_UIBATCH_H_
#define CODEHERO_UI_UIBATCH_H_

namespace CodeHero {

class Texture;
class VertexBuffer;

class UIBatch {
public:
    void SetTexture(std::shared_ptr<Texture> iTexture);
    void SetVertexBuffer();

    std::shared_ptr<Texture> GetTexture() const { return m_pTexture; }

private:
    std::shared_ptr<Texture> m_pTexture;
};

} // namespace CodeHero

#endif // CODEHERO_UI_UIBATCH_H_
