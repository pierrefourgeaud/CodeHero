// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_CAMERA_H_
#define CODEHERO_GRAPHICS_CAMERA_H_ 

#include "core/math/vector3.h"
#include "core/math/matrix4.h"

namespace CodeHero {

class Camera {
public:
    Camera();
    Camera(const Vector3& iPosition, const Vector3& iTarget);
    ~Camera();

    const Matrix4& GetView();

    void SetPosition(const Vector3& iPosition);
    void SetTarget(const Vector3& iTarget);

private:
    Vector3 m_Position;
    Vector3 m_Target;
    // Cached view matrix
    Matrix4 m_View;
    bool m_ViewDirty = true;

    void _ComputeViewMatrix();
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_CAMERA_H_
