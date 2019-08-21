// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_BATCH_H_
#define CODEHERO_GRAPHICS_BATCH_H_

#include <memory>
#include <vector>
#include "core/math/matrix4.h"

namespace CodeHero {

// Forward declaration
class Camera;
class Material;
class Mesh;
class RenderSystem;

class Batch {
public:
    void Draw(RenderSystem& iRS, const std::shared_ptr<Camera>& iCamera);

    void SetMaterial(const std::shared_ptr<Material>& iMaterial);
    void SetMesh(const std::shared_ptr<Mesh>& iMesh);
    void SetWorldTransform(const Matrix4& iWorldTransform);
    void SetDistanceFromCamera(const float& iDistanceFromCamera);
    void SetVertexDirLights(std::vector<float>* iVertex);
    void SetVertexPointLights(std::vector<float>* iVertex);

    std::shared_ptr<Material> GetMaterial() const { return m_pMaterial; }
    std::shared_ptr<Mesh> GetMesh() const { return m_pMesh; }
    const Matrix4& GetWorldTransform() const { return m_WorldTransform; }
    float GetDistanceFromCamera() const { return m_DistanceFromCamera; }

private:
    std::shared_ptr<Material> m_pMaterial;
    std::shared_ptr<Mesh> m_pMesh;
    Matrix4 m_WorldTransform;
    float m_DistanceFromCamera;

    // WeakPtrs here. The lights are guarantied to outlive the batch
    std::vector<float>* m_pVertexDirLights = nullptr;
    std::vector<float>* m_pVertexPointLights = nullptr;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_BATCH_H_
