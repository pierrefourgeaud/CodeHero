// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_CAMERA_H_
#define CODEHERO_GRAPHICS_CAMERA_H_ 

#include "core/math/vector3.h"
#include "core/math/matrix4.h"
#include "graphics/drawable.h"

namespace CodeHero {

class Camera : public Drawable {
public:
    OBJECT(Camera, Drawable)

    Camera(const std::shared_ptr<EngineContext>& iContext);
    ~Camera();

    void SetNearClip(float iNearClip);
    void SetFarClip(float iFarClip);
    void SetFov(float iFov);
    void SetAspectRatio(float iAspectRatio);

    const Matrix4& GetView();
    const Matrix4& GetProjection();

private:
    // Cached view matrix
    Matrix4 m_View;
    // Cached project matrix
    Matrix4 m_Projection;

    bool m_ProjectionDirty = true; // Dirty to be computed the first time

    float m_NearClip;
    float m_FarClip;
    float m_Fov;
    float m_AspectRatio;

    void _ComputeViewMatrix();
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_CAMERA_H_
