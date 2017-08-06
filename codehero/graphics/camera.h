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
    OBJECT(Camera)

    Camera(const std::shared_ptr<EngineContext>& iContext);
    ~Camera();

    const Matrix4& GetView();

private:
    // Cached view matrix
    Matrix4 m_View;

    void _ComputeViewMatrix();
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_CAMERA_H_
