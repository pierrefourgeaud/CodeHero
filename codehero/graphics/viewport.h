// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_VIEWPORT_H_
#define CODEHERO_GRAPHICS_VIEWPORT_H_

#include "core/math/vector2.h"
#include "core/typedefs.h"

namespace CodeHero {

// Forward declarations
class Camera;
class Scene;

class Viewport {
public:
    Viewport(uint32_t iX, uint32_t iY, uint32_t iWidth, uint32_t iHeight);
    Viewport(const IntVector2& iPosition, const IntVector2& iDimension);
    ~Viewport();

    IntVector2 GetPosition() const { return m_Position; }
    IntVector2 GetDimension() const { return m_Dimension; }
    uint32_t x() const { return m_Position.x(); }
    uint32_t y() const { return m_Position.y(); }
    uint32_t width() const { return m_Dimension.x(); }
    uint32_t height() const { return m_Dimension.y(); }

    void SetCamera(std::shared_ptr<Camera> iCamera) { m_pCamera = iCamera; }
    void SetScene(std::shared_ptr<Scene> iScene) { m_pScene = iScene; }

    const std::shared_ptr<Scene>& GetScene() const { return m_pScene; }
    const std::shared_ptr<Camera>& GetCamera() const { return m_pCamera; }

private:
    IntVector2 m_Position;
    IntVector2 m_Dimension;

    std::shared_ptr<Scene> m_pScene;
    std::shared_ptr<Camera> m_pCamera;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_VIEWPORT_H_
