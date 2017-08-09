// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/camera.h"
#include "graphics/node.h"
#include "core/math/matrix3.h"
#include "core/assert.h"

namespace CodeHero {

Camera::Camera(const std::shared_ptr<EngineContext>& iContext)
    : Drawable(iContext, DT_Camera) {}

Camera::~Camera() {}

const Matrix4& Camera::GetView() {
    if (m_IsDirty) {
        _ComputeViewMatrix();
        SetIsDirty(false);
    }

    return m_View;
}

void Camera::_ComputeViewMatrix() {
    std::shared_ptr<Node> node = m_pNode.lock();

    CH_ASSERT(node.get());

    Vector3 pos = node->GetPosition();

    m_View = Matrix4(node->GetRotation().RotationMatrix().Transpose());
    m_View.Set(3, 0, -Vector3({m_View.Get(0, 0), m_View.Get(1, 0), m_View.Get(2, 0)}).Dot(pos));
    m_View.Set(3, 1, -Vector3({m_View.Get(0, 1), m_View.Get(1, 1), m_View.Get(2, 1)}).Dot(pos));
    m_View.Set(3, 2, -Vector3({m_View.Get(0, 2), m_View.Get(1, 2), m_View.Get(2, 2)}).Dot(pos));
}

} // namespace CodeHero

