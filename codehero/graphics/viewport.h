// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_VIEWPORT_H_
#define CODEHERO_GRAPHICS_VIEWPORT_H_ 

#include "core/typedefs.h"
#include "core/math/vector2.h"

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

    void SetCamera(Camera* iCamera) { m_pCamera = iCamera; }
    void SetScene(Scene* iScene) { m_pScene = iScene; }

private:
    IntVector2 m_Position;
    IntVector2 m_Dimension;

    Scene* m_pScene;
    Camera* m_pCamera;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_VIEWPORT_H_
